#include "data/regex.h"
#include <greatest.h>

typedef struct
{
	char regex[256];
	char subject[MAX_STRING_CHARS];
	char* values[MAX_STRING_CHARS];
} EXPECT_PCRE2;

TEST test_regexMatch()
{
	EXPECT_PCRE2 expects[3] = { { "\\d+", "hello123world456yes789", { "123", "456", "789" } },
		{ "\\d+", "123world456yes789", { "123", "456", "789" } },
		{ "^([a-z0-9\\+_\\-]+)(\\.[a-z0-9\\+_\\-]+)*@([a-z0-9\\-]+\\.)+[a-z]{2,6}$", "suxlolz1528@gmail.com",
			{ "suxlolz1528@gmail.com" } } };

	PCRE2_VALUES* matches = NULL;
	for (int i = 0; i < 3; i++)
	{
		matches = PCRE2_Match((PCRE2_SPTR)expects[i].subject, (PCRE2_SPTR)expects[i].regex);
		for (int j = 0; matches != NULL && j < matches->count; j++)
			ASSERT_STR_EQ(matches->results[j].string, expects[i].values[j]);
		PCRE2_FreeValues(matches);
	}
	PASS();
}

TEST test_regexSplit()
{
	EXPECT_PCRE2 expects[3] = { { "\\d+", "hello123world456yes789", { "hello", "world", "yes" } },
		{ "\\d+", "123world456yes789", { "world", "yes" } },
		{ "^([a-z0-9\\+_\\-]+)(\\.[a-z0-9\\+_\\-]+)*@([a-z0-9\\-]+\\.)+[a-z]{2,6}$", "suxlolz1528@gmail.com", { 0 } } };

	PCRE2_VALUES* splits = NULL;
	for (int i = 0; i < 3; i++)
	{
		splits = PCRE2_Split((PCRE2_SPTR)expects[i].subject, (PCRE2_SPTR)expects[i].regex);
		for (int j = 0; splits != NULL && j < splits->count; j++)
			ASSERT_STR_EQ(splits->results[j].string, expects[i].values[j]);
		PCRE2_FreeValues(splits);
	}
	PASS();
}

TEST test_regexReplace()
{
	EXPECT_PCRE2 expects[3] = { { "\\d+", "hello123world456yes789", { "hello_world_yes_" } },
		{ "\\d+", "123world456yes789", { "_world_yes_" } },
		{ "^([a-z0-9\\+_\\-]+)(\\.[a-z0-9\\+_\\-]+)*@([a-z0-9\\-]+\\.)+[a-z]{2,6}$", "suxlolz1528@gmail.com",
			{ "_" } } };
	const char* replace = "_";
	char* string = NULL;

	for (int i = 0; i < 3; i++)
	{
		string = PCRE2_Replace((PCRE2_SPTR)expects[i].subject, (PCRE2_SPTR)expects[i].regex, replace);
		ASSERT_STR_EQ(string, expects[i].values[0]);
		free(string);
	}
	PASS();
}

SUITE(Suite_data_regex)
{
	RUN_TEST(test_regexMatch);
	RUN_TEST(test_regexSplit);
	RUN_TEST(test_regexReplace);
}
