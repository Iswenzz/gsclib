#include "regex.h"

#include <cgsc.h>
#include <stdlib.h>
#include <string.h>

void GScr_RegexSplit()
{
    CHECK_PARAMS(2, "Usage: RegexSplit(<string>, <regex>)");

    const char* subject = Plugin_Scr_GetString(0);
    const char* regex = Plugin_Scr_GetString(1);

    PCRE2_VALUES* splits = PCRE2_Split((PCRE2_SPTR)subject, (PCRE2_SPTR)regex);
    if (splits == NULL) return;

    Plugin_Scr_MakeArray();
    for (int i = 0; i < splits->count; i++)
    {
        Plugin_Scr_AddString(splits->results[i].string);
        Plugin_Scr_AddArray();
    }
    PCRE2_FreeValues(splits);
}

void GScr_RegexMatch()
{
    CHECK_PARAMS(2, "Usage: RegexMatch(<string>, <regex>)");

    const char* subject = Plugin_Scr_GetString(0);
    const char* regex = Plugin_Scr_GetString(1);

    PCRE2_VALUES* matches = PCRE2_Match((PCRE2_SPTR)subject, (PCRE2_SPTR)regex);
    if (matches == NULL) return;

    Plugin_Scr_MakeArray();
    for (int i = 0; i < matches->count; i++)
    {
        Plugin_Scr_AddString(matches->results[i].string);
        Plugin_Scr_AddArray();
    }
    PCRE2_FreeValues(matches);
}

void GScr_RegexReplace()
{
    CHECK_PARAMS(3, "Usage: RegexReplace(<string>, <replace>, <regex>)");

    const char* subject = Plugin_Scr_GetString(0);
    const char* replace = Plugin_Scr_GetString(1);
    const char* regex = Plugin_Scr_GetString(2);

    char* string = PCRE2_Replace((PCRE2_SPTR)subject, (PCRE2_SPTR)regex, replace);
    if (string == NULL) return;

    Plugin_Scr_AddString(string);
    free(string);
}

qboolean PCRE2_GetUTFOption(pcre2_code* re, uint32_t* optionBits)
{
    pcre2_pattern_info(re, PCRE2_INFO_ALLOPTIONS, optionBits);
    return (*optionBits & PCRE2_UTF) != 0;
}

qboolean PCRE2_IsNewlineCRLF(pcre2_code* re, uint32_t* newline)
{
    pcre2_pattern_info(re, PCRE2_INFO_NEWLINE, newline);
    return *newline == PCRE2_NEWLINE_ANY ||
        *newline == PCRE2_NEWLINE_CRLF ||
        *newline == PCRE2_NEWLINE_ANYCRLF;
}

qboolean PCRE2_HasMatches(int rc, pcre2_code* re, pcre2_match_data* matchData)
{
    if (rc < 0)
    {
        switch (rc)
        {
        case PCRE2_ERROR_NOMATCH:
            break;
        default:
            Plugin_Scr_Error(fmt("Matching error %d\n", rc));
            break;
        }
        pcre2_match_data_free(matchData);
        pcre2_code_free(re);
        return qfalse;
    }
    return qtrue;
}

qboolean PCRE2_CompileSuccess(pcre2_code* re, int* errorCode, PCRE2_SIZE* errorOffset)
{
    if (re != NULL)
        return qtrue;

    PCRE2_UCHAR buffer[256];
    pcre2_get_error_message(*errorCode, buffer, sizeof(buffer));

    Plugin_Scr_Error(fmt("PCRE2 compilation failed at offset %d: %s\n", *(int*)errorOffset, buffer));
    pcre2_code_free(re);
    return qfalse;
}

void PCRE2_AddValue(PCRE2_VALUE* value, char* string, int length, PCRE2_VALUES* values)
{
    if (values->results == NULL)
        values->results = (PCRE2_VALUE*)calloc(1, sizeof(PCRE2_VALUE));
    else
    {
        PCRE2_VALUE* temp = (PCRE2_VALUE*)realloc(values->results, (values->count + 1) * sizeof(PCRE2_VALUE));
        if (temp != NULL) values->results = temp;
    }
    values->results[values->count] = *value;
    strncpy(values->results[values->count].string, string, length);
    values->results[values->count].string[length] = '\0';
    values->count++;
}

PCRE2_VALUES* PCRE2_Compile(PCRE2_SPTR subject, PCRE2_SPTR regex)
{
    PCRE2_SIZE subjectLength = strlen((char *)subject);
    PCRE2_SIZE errorOffset;
    const int groupIndex = 0; // Capturing groups won't be part of the result values.
    int errorCode;
    int vectorMatchesCount = 0;
    PCRE2_VECTOR vectors[subjectLength + 1];
    PCRE2_VALUES* values = (PCRE2_VALUES*)calloc(1, sizeof(PCRE2_VALUES));

    pcre2_code* re = pcre2_compile(regex, PCRE2_ZERO_TERMINATED, 0, &errorCode, &errorOffset, NULL);
    if (!PCRE2_CompileSuccess(re, &errorCode, &errorOffset))
    {
        free(values);
        return NULL;
    }

    pcre2_match_data* matchData = pcre2_match_data_create_from_pattern(re, NULL);
    int rc = pcre2_match(re, subject, subjectLength, 0, 0, matchData, NULL);
    if (!PCRE2_HasMatches(rc, re, matchData))
    {
        free(values);
        return NULL;
    }

    PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(matchData);
    vectors[vectorMatchesCount].position = subject + ovector[2 * groupIndex] - subject;
    vectors[vectorMatchesCount].length = ovector[2 * groupIndex + 1] - ovector[2 * groupIndex];
    vectorMatchesCount++;

    uint32_t optionBits;
    qboolean utf8 = PCRE2_GetUTFOption(re, &optionBits);

    uint32_t newline;
    qboolean isNewlineCRLF = PCRE2_IsNewlineCRLF(re, &newline);

    // Find sub matches
    for (;;)
    {
        uint32_t options = 0;
        PCRE2_SIZE startOffset = ovector[1];

        /* If the previous match was for an empty subject, we are finished if we are
        at the end of the subject. Otherwise, arrange to run another match at the
        same point to see if a non-empty match can be found. */

        if (ovector[0] == ovector[1])
        {
            if (ovector[0] == subjectLength) break;
            options = PCRE2_NOTEMPTY_ATSTART | PCRE2_ANCHORED;
        }

        rc = pcre2_match(re, subject, subjectLength, startOffset, options, matchData, NULL);
        if (rc == PCRE2_ERROR_NOMATCH)
        {
            if (options == 0) break;
            ovector[1] = startOffset + 1;

            // If CRLF is a newline advance by one more character
            if (isNewlineCRLF && startOffset < subjectLength - 1 &&
                subject[startOffset] == '\r' && subject[startOffset + 1] == '\n')
                ovector[1] += 1;
            else if (utf8)
            {
                // Otherwise, ensure we advance a whole UTF-8 character
                while (ovector[1] < subjectLength)
                {
                    if ((subject[ovector[1]] & 0xc0) != 0x80) break;
                    ovector[1] += 1;
                }
            }
            continue;
        }
        if (!PCRE2_HasMatches(rc, re, matchData))
            break;

        vectors[vectorMatchesCount].position = subject + ovector[2 * groupIndex] - subject;
        vectors[vectorMatchesCount].length = ovector[2 * groupIndex + 1] - ovector[2 * groupIndex];
        vectorMatchesCount++;
    }

    // Build values
    for (int i = 0; i < vectorMatchesCount; i++)
    {
        PCRE2_VALUE value = { 0 };
        PCRE2_VECTOR current = vectors[i];
        PCRE2_VECTOR last = vectors[i - 1];

        // Check for unmatched string
        if (current.position != 0)
        {
            if (!i)
            {
                int length = current.position;
                value.matched = qfalse;
                PCRE2_AddValue(&value, (char *)subject, length, values);
            }
            else if (i > 0)
            {
                int pos = last.position + last.length;
                if (pos != current.position)
                {
                    int length = current.position - pos;
                    value.matched = qfalse;
                    PCRE2_AddValue(&value, (char*)subject + pos, length, values);
                }
            }
        }

        // Matched string
        value.matched = qtrue;
        PCRE2_AddValue(&value, (char*)subject + current.position, current.length, values);
    }
    pcre2_match_data_free(matchData);
    pcre2_code_free(re);

    return values;
}

void PCRE2_FreeValues(PCRE2_VALUES* values)
{
    if (values != NULL)
    {
        if (values->results != NULL)
            free(values->results);
        free(values);
    }
    values = NULL;
}

PCRE2_VALUES* PCRE2_Match(PCRE2_SPTR subject, PCRE2_SPTR regex)
{
    PCRE2_VALUES* matches = (PCRE2_VALUES*)calloc(1, sizeof(PCRE2_VALUES));
    PCRE2_VALUES* values = PCRE2_Compile(subject, regex);

    for (int i = 0; i < values->count; i++)
    {
        if (values->results[i].matched)
        {
            PCRE2_AddValue(&values->results[i], values->results[i].string,
                strlen(values->results[i].string), matches);
        }
    }
    PCRE2_FreeValues(values);
    return matches;
}

PCRE2_VALUES* PCRE2_Split(PCRE2_SPTR subject, PCRE2_SPTR regex)
{
    PCRE2_VALUES* splits = (PCRE2_VALUES*)calloc(1, sizeof(PCRE2_VALUES));
    PCRE2_VALUES* values = PCRE2_Compile(subject, regex);

    for (int i = 0; i < values->count; i++)
    {
        if (!values->results[i].matched)
        {
            PCRE2_AddValue(&values->results[i], values->results[i].string,
                strlen(values->results[i].string), splits);
        }
    }
    PCRE2_FreeValues(values);
    return splits;
}

char* PCRE2_Replace(PCRE2_SPTR subject, PCRE2_SPTR regex, const char* replace)
{
    char* string = (char*)calloc(MAX_STRING_CHARS, sizeof(char));
    PCRE2_VALUES* values = PCRE2_Compile(subject, regex);

    for (int i = 0; i < values->count; i++)
        strcat(string, !values->results[i].matched ? values->results[i].string : replace);
    PCRE2_FreeValues(values);
    return string;
}
