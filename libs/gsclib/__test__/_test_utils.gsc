#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Utils");

	// utils/stringutils
	it(::test_ToUpper, "ToUpper");
	it(::test_IsNullOrEmpty, "IsNullOrEmpty");
	it(::test_IsStringInt, "IsStringInt");
	it(::test_IsStringAlpha, "IsStringAlpha");
	it(::test_IsStringFloat, "IsStringFloat");
	it(::test_ToRGB, "ToRGB");
	it(::test_HexToRGB, "HexToRGB");
	it(::test_Fmt, "Fmt");
	it(::test_Trim, "Trim");
	it(::test_StartsWith, "StartsWith");
	it(::test_EndsWith, "EndsWith");
	it(::test_StrJoin, "StrJoin");
	it(::test_StrReplace, "StrReplace");
	it(::test_PathJoin, "PathJoin");

	// utils/utils
	it(::test_GetType, "GetType");
	it(::test_Ternary, "Ternary");
	it(::test_IfUndef, "IfUndef");
	it(::test_ToInt, "ToInt");
	it(::test_ToFloat, "ToFloat");
	it(::test_ToString, "ToString");
}

test_StrReplace()
{
	EXPECT_EQ(StrReplace("SR Speedrun", "Speedrun", "Deathrun"), "SR Deathrun");
}

test_StrJoin()
{
	EXPECT_EQ(StrJoin(level.tests.strings, "-"), "Ellin-Alexa-Celiza-Iswenzz-10");
}

test_PathJoin()
{
	EXPECT_GT(PathJoin("/home", "cod4", "speedrun").size, 10);
	EXPECT_GT(PathJoin("C:\\home", "cod4", "speedrun").size, 10);
}

test_StartsWith()
{
	EXPECT_TRUE(StartsWith("hello world", "hello"));
	EXPECT_FALSE(StartsWith("hello world", "world"));
}

test_EndsWith()
{
	EXPECT_FALSE(EndsWith("hello world", "hello"));
	EXPECT_TRUE(EndsWith("hello world", "world"));
}

test_Trim()
{
	EXPECT_EQ(trim("   hello world    "), "hello world");
}

test_Fmt()
{
	EXPECT_EQ(fmt("%d %d", 1, 2), "1 2");
	EXPECT_EQ(fmt("%f %s", 1.4, "test"), "1.400000 test");
	EXPECT_EQ(fmt("%s %s", "hello", "world"), "hello world");
	EXPECT_EQ(fmt("%s", undefined), "<error>");
}

test_GetType()
{
	EXPECT_EQ(GetType(1.125), "FLOAT");
	EXPECT_EQ(GetType(10), "INTEGER");
	EXPECT_EQ(GetType("test"), "STRING");
	EXPECT_EQ(GetType((0, 1, 2)), "VECTOR");
}

test_Ternary()
{
	EXPECT_EQ(Ternary(true, 3, 4), 3);
	EXPECT_EQ(Ternary(false, 3, 4), 4);
}

test_IfUndef()
{
	EXPECT_EQ(IfUndef(undefined, "test"), "test");
	EXPECT_EQ(IfUndef("test", undefined), "test");
}

test_IsNullOrEmpty()
{
	EXPECT_EQ(IsNullOrEmpty(undefined), true);
	EXPECT_EQ(IsNullOrEmpty(""), true);
	EXPECT_EQ(IsNullOrEmpty("test"), false);
}

test_ToUpper()
{
	EXPECT_EQ(ToUpper("test"), "TEST");
	EXPECT_EQ(ToUpper("test2"), "TEST2");
	EXPECT_EQ(ToUpper("test__test"), "TEST__TEST");
}

test_ToInt()
{
	EXPECT_EQ(ToInt("1"), 1);
	EXPECT_EQ(ToInt(2.2), 2);
	EXPECT_EQ(ToInt((3, 3, 3)), 9);
}

test_ToFloat()
{
	EXPECT_EQ(ToFloat("1.1"), 1.1);
	EXPECT_EQ(ToFloat(2.2), 2.2);
	EXPECT_EQ(ToFloat((3.3, 3.3, 3.3)), 9.9);
}

test_ToString()
{
	EXPECT_EQ(ToString("1"), "1");
	EXPECT_EQ(ToString(2.2), "2.200000");
	EXPECT_EQ(ToString((3.3, 3.3, 3.3)), "(3.300000, 3.300000, 3.300000)");
}

test_IsStringInt()
{
	EXPECT_EQ(IsStringInt("123"), true);
	EXPECT_EQ(IsStringInt("123__"), false);
	EXPECT_EQ(IsStringInt("123.123"), false);
	EXPECT_EQ(IsStringInt("ab123__"), false);
	EXPECT_EQ(IsStringInt("test"), false);
}

test_IsStringAlpha()
{
	EXPECT_EQ(IsStringAlpha("123"), false);
	EXPECT_EQ(IsStringAlpha("123__"), false);
	EXPECT_EQ(IsStringAlpha("123.123"), false);
	EXPECT_EQ(IsStringAlpha("ab123__"), false);
	EXPECT_EQ(IsStringAlpha("test"), true);
}

test_IsStringFloat()
{
	EXPECT_EQ(IsStringFloat("123.123"), true);
	EXPECT_EQ(IsStringFloat("123.123__"), false);
	EXPECT_EQ(IsStringFloat("123"), true);
	EXPECT_EQ(IsStringFloat("ab123.123__"), false);
	EXPECT_EQ(IsStringFloat("test"), false);
}

test_ToRGB()
{
	EXPECT_EQ(ToRGB(125, 125, 255), (0.490196, 0.490196, 1));
}

test_HexToRGB()
{
	EXPECT_EQ(HexToRGB("AABBCC"), (0.666667, 0.733333, 0.8));
	EXPECT_EQ(HexToRGB("#AABBCC"), (0.666667, 0.733333, 0.8));
	EXPECT_EQ(HexToRGB("#FFFFFF"), (1, 1, 1));
}
