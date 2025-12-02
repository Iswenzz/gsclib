#pragma once
#define PCRE2_CODE_UNIT_WIDTH 8

#include <CGSC/cgsc.h>
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

void GScr_RegexSplit();
void GScr_RegexMatch();
void GScr_RegexReplace();

qboolean PCRE2_GetUTFOption(pcre2_code* re, uint32_t* optionBits);
qboolean PCRE2_IsNewlineCRLF(pcre2_code* re, uint32_t* newline);
qboolean PCRE2_HasMatches(int rc, pcre2_code* re, pcre2_match_data* matchData);
qboolean PCRE2_CompileSuccess(pcre2_code* re, int* errorCode, PCRE2_SIZE* errorOffset);
void PCRE2_AddValue(PCRE2_VALUE* value, char* string, int length, PCRE2_VALUES* values);
PCRE2_VALUES* PCRE2_Compile(PCRE2_SPTR subject, PCRE2_SPTR regex);
void PCRE2_FreeValues(PCRE2_VALUES* values);
PCRE2_VALUES* PCRE2_Match(PCRE2_SPTR subject, PCRE2_SPTR regex);
PCRE2_VALUES* PCRE2_Split(PCRE2_SPTR subject, PCRE2_SPTR regex);
char* PCRE2_Replace(PCRE2_SPTR subject, PCRE2_SPTR regex, const char* replace);
