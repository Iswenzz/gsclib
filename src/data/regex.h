#pragma once
#include <dre2.h>

typedef struct
{
	size_t count;
	unsigned char **items;
} regex_items;

regex_items *dre2_get_matches(struct dre2 *re, unsigned char *input);
regex_items *dre2_get_splits(struct dre2 *re, unsigned char *input);
void cleanup_dre2_matches(regex_items *matches);

void GScr_RegexMatch();
void GScr_RegexReplace();
void GScr_RegexSplit();