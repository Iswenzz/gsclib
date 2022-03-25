#include sr\tests\_main;

// Tests for gsclib/data
test()
{
	suit("GSCLIB - Data");

	// data/regex
	run(::it_RegexMatch, "RegexMatch");
	run(::it_RegexReplace, "RegexReplace");
	run(::it_RegexSplit, "RegexSplit");
}

it_RegexMatch()
{
	printArray(RegexMatch("zzzz123affff12345ffffb", "\\d+"));
}

it_RegexSplit()
{
	printArray(RegexSplit("zzzz123affff12345ffffb", "\\d+"));
}

it_RegexReplace()
{
	printVariable(RegexReplace("zzzz123affff12345ffffb", "", "\\d+"));
}
