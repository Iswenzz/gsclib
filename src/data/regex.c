#include "regex.h"
#include <cgsc.h>
#include <stdlib.h>
#include <string.h>

regex_items *dre2_get_matches(struct dre2 *re, unsigned char *input)
{
	regex_items *matches = malloc(sizeof(regex_items));
	matches->count = 0;
	matches->items = NULL;

	// Check if input strings match the regex
	unsigned char *it_match = (unsigned char *)calloc(strlen((const char *)input), sizeof(unsigned char));
	struct dre2_match_value result = dre2_match(re, input);
	unsigned char *p = input;

	while (result.matched)
	{
		// Resize matches array
		matches->count++;
		if (matches->items == NULL)
			matches->items = (unsigned char **)malloc(matches->count * sizeof(unsigned char *));
		else
		{
			unsigned char **temp = (unsigned char **)realloc(matches->items, matches->count * sizeof(unsigned char *));
			if (temp != NULL)
				matches->items = temp;
		}

		// Get match string
		dre2_matched_substring(p, &result, &it_match);
		matches->items[matches->count - 1] = (unsigned char *)calloc(strlen((const char *)it_match), sizeof(unsigned char));
		strncpy((char *)matches->items[matches->count - 1], (char *)it_match, strlen((const char *)it_match));

		// Sub matched string from input string
		p += result.end_pos;
		result = dre2_match(re, p);
	}
	free(it_match);
	it_match = NULL;
	return matches;
}

regex_items *dre2_get_splits(struct dre2 *re, unsigned char *input)
{
	regex_items *splits = malloc(sizeof(regex_items));
	splits->count = 0;
	splits->items = NULL;

	// Check if input strings match the regex
	unsigned char *it_match = (unsigned char *)calloc(strlen((const char *)input), sizeof(unsigned char));
	struct dre2_match_value result = dre2_match(re, input);
	unsigned char *p = input;

	while (result.matched)
	{
		// Resize splits array
		splits->count++;
		if (splits->items == NULL)
			splits->items = (unsigned char **)malloc(splits->count * sizeof(unsigned char *));
		else
		{
			unsigned char **temp = (unsigned char **)realloc(splits->items, splits->count * sizeof(unsigned char *));
			if (temp != NULL)
				splits->items = temp;
		}

		// Get split string
		dre2_matched_substring(p, &result, &it_match);
		splits->items[splits->count - 1] = (unsigned char *)calloc(result.start_pos + 1, sizeof(unsigned char));
		memcpy(splits->items[splits->count - 1], p, result.start_pos);

		// Sub matched string from input string
		p += result.end_pos;
		result = dre2_match(re, p);
	}
	if (*p != '\0')
	{
		// Resize splits array
		splits->count++;
		if (splits->items == NULL)
			splits->items = (unsigned char **)malloc(splits->count * sizeof(unsigned char *));
		else
		{
			unsigned char **temp = (unsigned char **)realloc(splits->items, splits->count * sizeof(unsigned char *));
			if (temp != NULL)
				splits->items = temp;
		}

		// Get the last split
		splits->items[splits->count - 1] = (unsigned char *)calloc(strlen((const char *)p), sizeof(unsigned char));
		memcpy(splits->items[splits->count - 1], p, strlen((const char *)p));
	}

	free(it_match);
	it_match = NULL;
	return splits;
}

void cleanup_dre2_matches(regex_items *matches)
{
	for (int i = 0; i < matches->count; i++)
	{
		if (matches->items[i] != NULL)
		{
			free(matches->items[i]);
			matches->items[i] = NULL;
		}
	}
	free(matches);
	matches = NULL;
}

void GScr_RegexSplit()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: RegexSplit(<string>, <pattern>)");
		return;
	}
	unsigned char *input = (unsigned char *)Plugin_Scr_GetString(0);
	unsigned char *regex_pattern = (unsigned char *)Plugin_Scr_GetString(1);
	struct dre2 *re;

	// Parse the regex string into the dre2 object
	re = dre2_parse(regex_pattern, DRE2_GREEDY);
	if (re == NULL)
	{
		printf("RegexMatch(): Failed to parse!\n");
		return;
	}
	regex_items *splits = dre2_get_splits(re, input);

	if (splits->count > 0)
	{
		Plugin_Scr_MakeArray();
		for (int i = 0; i < splits->count; i++)
		{
			Plugin_Scr_AddString((const char *)splits->items[i]);
			Plugin_Scr_AddArray();
		}
	}
	else
		Plugin_Scr_AddUndefined();

	cleanup_dre2(re);
	cleanup_dre2_matches(splits);
}

void GScr_RegexReplace()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: RegexReplace(<string>, <replace_string>, <pattern>)");
		return;
	}
	unsigned char *input = (unsigned char *)Plugin_Scr_GetString(0);
	unsigned char *replace_str = (unsigned char *)Plugin_Scr_GetString(1);
	unsigned char *regex_pattern = (unsigned char *)Plugin_Scr_GetString(2);
	struct dre2 *re;

	// Parse the regex string into the dre2 object
	re = dre2_parse(regex_pattern, DRE2_GREEDY);
	if (re == NULL)
	{
		printf("RegexReplace(): Failed to parse!\n");
		return;
	}
	regex_items *splits = dre2_get_splits(re, input);
	size_t buffer_size = 1;
	unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char));

	if (splits->count > 0)
	{
		for (int i = 0; i < splits->count; i++)
		{
			int strSize = snprintf(NULL, 0, "%s%s", splits->items[i], replace_str);
			buffer_size += strSize;
			unsigned char *temp = (unsigned char *)realloc(buffer, buffer_size * sizeof(unsigned char));
			if (temp != NULL)
			{
				buffer = temp;
				snprintf((char *)(buffer + buffer_size - strSize - 1), buffer_size, "%s%s", splits->items[i], replace_str);
			}
		}
		Plugin_Scr_AddString((const char *)buffer);
	}
	else
		Plugin_Scr_AddUndefined();

	cleanup_dre2(re);
	cleanup_dre2_matches(splits);
	free(buffer);
}

void GScr_RegexMatch()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: RegexMatch(<string>, <pattern>)");
		return;
	}
	unsigned char *input = (unsigned char *)Plugin_Scr_GetString(0);
	unsigned char *regex_pattern = (unsigned char *)Plugin_Scr_GetString(1);
	struct dre2 *re;

	// Parse the regex string into the dre2 object
	re = dre2_parse(regex_pattern, DRE2_GREEDY);
	if (re == NULL)
	{
		printf("RegexMatch(): Failed to parse!\n");
		return;
	}
	regex_items *matches = dre2_get_matches(re, input);

	if (matches->count > 0)
	{
		Plugin_Scr_MakeArray();
		for (int i = 0; i < matches->count; i++)
		{
			Plugin_Scr_AddString((const char *)matches->items[i]);
			Plugin_Scr_AddArray();
		}
	}
	else
		Plugin_Scr_AddUndefined();

	cleanup_dre2(re);
	cleanup_dre2_matches(matches);
}
