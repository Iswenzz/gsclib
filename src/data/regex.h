#pragma once
#define PCRE2_CODE_UNIT_WIDTH 8

#include <cgsc.h>
#include <pcre2.h>

typedef struct
{
    char string[MAX_STRING_CHARS];
    qboolean matched;
} PCRE2_VALUE;

typedef struct
{
    PCRE2_VALUE* results;
    size_t count;
} PCRE2_VALUES;

typedef struct
{
    int position;
    size_t length;
} PCRE2_VECTOR;

/// <summary>
/// Get all splited string in an array from the specified input stringand regex.
/// </summary>
void GScr_RegexSplit();

/// <summary>
/// Get all matches in an array from the specified input string and regex.
/// </summary>
void GScr_RegexMatch();

/// <summary>
/// Replace all matches with a specific string.
/// </summary>
void GScr_RegexReplace();

/// <summary>
/// Get the options with which the regex was compiled and extract the UTF state.
/// </summary>
/// <param name="re">The re code.</param>
/// <param name="optionBits">The out option bits</param>
/// <returns></returns>
qboolean PCRE2_GetUTFOption(pcre2_code* re, uint32_t* optionBits);

/// <summary>
/// Find the newline convention and see whether CRLF is a valid newline sequence.
/// </summary>
/// <param name="re">The re code.</param>
/// <param name="newline">The out newline.</param>
/// <returns></returns>
qboolean PCRE2_IsNewlineCRLF(pcre2_code* re, uint32_t* newline);

/// <summary>
/// Check if a match data contains matches.
/// </summary>
/// <param name="rc">The match RC from pcre2_match.</param>
/// <param name="re">The re code.</param>
/// <param name="matchData">The match data.</param>
/// <returns></returns>
qboolean PCRE2_HasMatches(int rc, pcre2_code* re, pcre2_match_data* matchData);

/// <summary>
/// Check if a re successfully compiled.
/// </summary>
/// <param name="re">The re code.</param>
/// <param name="errorCode">The out error code.</param>
/// <param name="errorOffset">The out error offset.</param>
/// <returns></returns>
qboolean PCRE2_CompileSuccess(pcre2_code* re, int* errorCode, PCRE2_SIZE* errorOffset);

/// <summary>
/// Add a value to the provided values struct.
/// </summary>
/// <param name="value">The ref to a new value.</param>
/// <param name="string">The string to add.</param>
/// <param name="length">The length of the string.</param>
/// <param name="values">The pointer to the values struct.</param>
void PCRE2_AddValue(PCRE2_VALUE* value, char* string, int length, PCRE2_VALUES* values);

/// <summary>
/// Compile a regex with the provided string and gets all different occurences type.
/// </summary>
/// <param name="subject">The string to test with a regex.</param>
/// <param name="regex">The regex pattern.</param>
/// <returns></returns>
PCRE2_VALUES* PCRE2_Compile(PCRE2_SPTR subject, PCRE2_SPTR regex);

/// <summary>
/// Free the values.
/// </summary>
/// <param name="values">The values pointer struct.</param>
void PCRE2_FreeValues(PCRE2_VALUES* values);

/// <summary>
/// Get all matches from the provided string and regex pattern.
/// </summary>
/// <param name="subject">The string to test with a regex.</param>
/// <param name="regex">The regex pattern.</param>
/// <returns></returns>
PCRE2_VALUES* PCRE2_Match(PCRE2_SPTR subject, PCRE2_SPTR regex);

/// <summary>
/// Get all splits from the provided string and regex pattern.
/// </summary>
/// <param name="subject">The string to test with a regex.</param>
/// <param name="regex">The regex pattern.</param>
/// <returns></returns>
PCRE2_VALUES* PCRE2_Split(PCRE2_SPTR subject, PCRE2_SPTR regex);

/// <summary>
/// Replace all matches from the provided string and regex pattern.
/// </summary>
/// <param name="subject">The string to test with a regex.</param>
/// <param name="regex">The regex pattern.</param>
/// <param name="replace">The string to replace all matches.</param>
/// <returns></returns>
char* PCRE2_Replace(PCRE2_SPTR subject, PCRE2_SPTR regex, char* replace);
