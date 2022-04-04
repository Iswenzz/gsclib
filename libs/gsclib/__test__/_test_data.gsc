#include libs\gscunit\_main;
#include libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB - Data");

	// data/regex
	it(::test_RegexMatch, "RegexMatch");
	it(::test_RegexReplace, "RegexReplace");
	it(::test_RegexSplit, "RegexSplit");
}

test_RegexMatch()
{
	matches = RegexMatch("hello123 world12345", "\\d+");
	EXPECT_CONTAIN(matches, "123");
	EXPECT_CONTAIN(matches, "12345");
}

test_RegexSplit()
{
	matches = RegexMatch("hello123 world12345", "\\d+");
	EXPECT_CONTAIN(matches, "hello");
	EXPECT_CONTAIN(matches, "world");
}

test_RegexReplace()
{
	EXPECT_EQ(RegexReplace("hello123 world12345", "", "\\d+"), "hello world");
}
