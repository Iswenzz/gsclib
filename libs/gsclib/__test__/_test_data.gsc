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
	matches = RegexMatch("hello123world456", "\\d+");
	EXPECT_CONTAIN(matches, "123");
	EXPECT_CONTAIN(matches, "456");

	emailPattern = "^([a-z0-9\\+_\\-]+)(\\.[a-z0-9\\+_\\-]+)*@([a-z0-9\\-]+\\.)+[a-z]{2,6}$";
	matches = RegexMatch("suxlolz1528@gmail.com", emailPattern);
	EXPECT_CONTAIN(matches, "suxlolz1528@gmail.com");
}

test_RegexSplit()
{
	matches = RegexSplit("hello123world456", "\\d+");
	EXPECT_CONTAIN(matches, "hello");
	EXPECT_CONTAIN(matches, "world");
}

test_RegexReplace()
{
	EXPECT_EQ(RegexReplace("123hello456world789", "_", "\\d+"), "_hello_world_");
}
