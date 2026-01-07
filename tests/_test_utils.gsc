#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Utils");

	// Utils/Linq
	it(::test_Select, "Select");
	it(::test_Foreach, "Foreach");
	it(::test_Aggregate, "Aggregate");
	it(::test_GetMin, "GetMin");
	it(::test_GetMax, "GetMax");
	it(::test_Cast, "Cast");
	it(::test_OfType, "OfType");
	it(::test_Sort, "Sort");
	it(::test_Average, "Average");
	it(::test_Sum, "Sum");
	it(::test_Range, "Range");
	it(::test_Repeat, "Repeat");
	it(::test_Reverse, "Reverse");
	it(::test_Concat, "Concat");
	it(::test_Chunk, "Chunk");
	it(::test_Contains, "Contains");
	it(::test_IndexOf, "IndexOf");
	it(::test_Remove, "Remove");
	it(::test_RemoveAt, "RemoveAt");
	it(::test_All, "All");
	it(::test_Any, "Any");
	it(::test_Where, "Where");
	it(::test_Last, "Last");
	it(::test_First, "First");
	it(::test_Count, "Count");

	// Utils/Math
	it(::test_fmod, "fmod");
	it(::test_tan1, "tan1");
	it(::test_atan1, "atan1");
	it(::test_atan2, "atan2");
	it(::test_cos1, "cos1");
	it(::test_acos1, "acos1");
	it(::test_sin1, "sin1");
	it(::test_asin1, "asin1");

	// Utils/Regex
	it(::test_RegexMatch, "RegexMatch");
	it(::test_RegexReplace, "RegexReplace");
	it(::test_RegexSplit, "RegexSplit");

	// Utils/Utils
	it(::test_ToInt, "ToInt");
	it(::test_ToFloat, "ToFloat");
	it(::test_ToString, "ToString");
	it(::test_GetType, "GetType");
	it(::test_Ternary, "Ternary");
	it(::test_IfUndef, "IfUndef");
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
	it(::test_Replace, "Replace");
	it(::test_PathJoin, "PathJoin");
}

test_IndexOf()
{
	EXPECT_EQ(IndexOf(level.tests.ints, 3), 3);
	EXPECT_EQ(IndexOf(level.tests.strings, "Iswenzz"), 3);
	EXPECT_EQ(IndexOf(level.tests.floats, 1.05), 1);
	EXPECT_EQ(IndexOf(level.tests.vectors, (1.05, 1.05, 1.05)), 1);
	EXPECT_EQ(IndexOf(level.tests.strings, "WrongValue"), -1);
}

test_Aggregate()
{
	EXPECT_EQ(Aggregate(0, level.tests.ints, ::delagateAggregateInt), 45);
}

test_Concat()
{
	EXPECT_EQ(Concat(level.tests.ints, level.tests.ints).size, 20);
}

test_Chunk()
{
	chunks = Chunk(level.tests.ints, 2);

	EXPECT_EQ(chunks.size, 5);
	EXPECT_EQ(chunks[0].size, 2);
}

test_Contains()
{
	EXPECT_TRUE(Contains(level.tests.ints, 1));
	EXPECT_FALSE(Contains(level.tests.ints, 100));
}

test_Foreach()
{
	ints = [];
	for (i = 0; i < 10; i++)
	{
		ints[i] = spawnStruct();
		ints[i].value = i;
	}

	Foreach(ints, ::delegateForeachIncrement);
	EXPECT_EQ(ints[0].value, 1);
	EXPECT_EQ(ints[1].value, 2);
}

test_All()
{
	EXPECT_EQ(All(level.tests.ints, ::predicate), false);
	EXPECT_EQ(All(level.tests.strings, ::predicateString), false);
	EXPECT_EQ(All(level.tests.vectors, ::predicateVector), false);
	EXPECT_EQ(All(level.tests.structs, ::predicateStructString), false);
	EXPECT_EQ(All(level.tests.arrays, ::predicateArray), false);
	EXPECT_EQ(All(level.tests.ents, ::predicateEnt), true);
}

test_Any()
{
	EXPECT_EQ(Any(level.tests.ints, ::predicate), true);
	EXPECT_EQ(Any(level.tests.strings, ::predicateString), true);
	EXPECT_EQ(Any(level.tests.vectors, ::predicateVector), true);
	EXPECT_EQ(Any(level.tests.structs, ::predicateStructString), true);
	EXPECT_EQ(Any(level.tests.arrays, ::predicateArray), true);
}

test_Where()
{
	EXPECT_NOT_CONTAIN(Where(level.tests.ints, ::predicate), 5);
	EXPECT_NOT_CONTAIN(Where(level.tests.strings, ::predicateString), "Iswenzz");
	EXPECT_NOT_CONTAIN(Where(level.tests.vectors, ::predicateVector), (0, 0, 0));
}

test_GetMin()
{
	EXPECT_EQ(GetMin(level.tests.ints), 0);
	EXPECT_EQ(GetMin(level.tests.strings), "10");
	EXPECT_EQ(GetMin(level.tests.vectors), (0, 0, 0));
}

test_GetMax()
{
	EXPECT_EQ(GetMax(level.tests.ints), 9);
	EXPECT_EQ(GetMax(level.tests.strings), "Iswenzz");
	EXPECT_EQ(GetMax(level.tests.vectors), (9.45, 9.45, 9.45));
}

test_Last()
{
	EXPECT_EQ(Last(level.tests.ints, ::predicate), 9);
	EXPECT_EQ(Last(level.tests.strings, ::predicateString), "10");
	EXPECT_EQ(Last(level.tests.vectors, ::predicateVector), (9.45, 9.45, 9.45));
	EXPECT_EQ(Last(level.tests.structs, ::predicateStructString).string, "Desert Eagle");
	EXPECT_EQ(Last(level.tests.arrays, ::predicateArray)[0].string, "AK47");
	EXPECT_CONTAIN(Last(level.tests.ents, ::predicateEnt).name, "bot");
}

test_First()
{
	EXPECT_EQ(First(level.tests.ints, ::predicate), 0);
	EXPECT_EQ(First(level.tests.strings, ::predicateString), "Ellin");
	EXPECT_EQ(First(level.tests.vectors, ::predicateVector), (1.05, 1.05, 1.05));
	EXPECT_EQ(First(level.tests.structs, ::predicateStructString).string, "AK47");
	EXPECT_EQ(First(level.tests.arrays, ::predicateArray)[0].string, "AK47");
	EXPECT_CONTAIN(First(level.tests.ents, ::predicateEnt).name, "bot");
}

test_Cast()
{
	casts = [];
	casts[casts.size] = "100";
	casts[casts.size] = 200;
	casts[casts.size] = 300.300;
	casts[casts.size] = (400, 400, 400);

	EXPECT_CONTAIN(Cast(casts, "string"), "100");
	EXPECT_CONTAIN(Cast(casts, "string"), "200");
	EXPECT_CONTAIN(Cast(casts, "string"), "300.3");
	EXPECT_CONTAIN(Cast(casts, "string"), "(400, 400, 400)");

	EXPECT_CONTAIN(Cast(casts, "int"), 100);
	EXPECT_CONTAIN(Cast(casts, "int"), 200);
	EXPECT_CONTAIN(Cast(casts, "int"), 300);

	EXPECT_CONTAIN(Cast(casts, "float"), 100);
	EXPECT_CONTAIN(Cast(casts, "float"), 200);
	EXPECT_CONTAIN(Cast(casts, "float"), 300.3);
}

test_OfType()
{
	vars = [];
	vars[vars.size] = "100";
	vars[vars.size] = 200;
	vars[vars.size] = 300.300;
	vars[vars.size] = (400, 400, 400);
	vars[vars.size] = level.tests.structs[0];
	vars[vars.size] = level.tests.ints;
	vars[vars.size] = level.tests.ents[0];

	EXPECT_EQ(OfType(vars, "string").size, 1);
	EXPECT_EQ(OfType(vars, "int").size, 1);
	EXPECT_EQ(OfType(vars, "float").size, 1);
	EXPECT_EQ(OfType(vars, "vector").size, 1);

	EXPECT_EQ(OfType(vars, "struct")[0].string, "AK47");
	EXPECT_EQ(OfType(vars, "array")[0].size, 10);
	EXPECT_CONTAIN(OfType(vars, "ent")[0].name, "bot");
}

test_Sort()
{
	EXPECT_EQ(Sort(level.tests.ints)[0], 0);
	EXPECT_EQ(Sort(level.tests.floats)[0], 0);
	EXPECT_EQ(Sort(level.tests.strings)[0], "10");
	EXPECT_EQ(Sort(level.tests.vectors)[0], (0, 0, 0));
}

test_Average()
{
	EXPECT_EQ(Average(level.tests.ints), 4.5);
	EXPECT_EQ(Average(level.tests.vectors), (4.725, 4.725, 4.725));
}

test_Count()
{
	EXPECT_EQ(Count(level.tests.ints, ::predicate), 9);
	EXPECT_EQ(Count(level.tests.floats, ::predicate), 10);
	EXPECT_EQ(Count(level.tests.strings, ::predicateString), 4);
	EXPECT_EQ(Count(level.tests.vectors, ::predicateVector), 9);
	EXPECT_EQ(Count(level.tests.structs, ::predicateStructString), 2);
	EXPECT_EQ(Count(level.tests.arrays, ::predicateArray), 1);
}

test_Sum()
{
	EXPECT_EQ(Sum(level.tests.ints), 45);
	EXPECT_EQ(ToInt(Sum(level.tests.floats)), 47);
	EXPECT_EQ(Sum(level.tests.strings), "EllinAlexaCelizaIswenzz10");
	EXPECT_EQ(ToInt(Sum(level.tests.vectors)) / 3, 47);
}

test_Select()
{
	EXPECT_CONTAIN(Select(level.tests.structs, ::delegateStructString), "AK47");
	EXPECT_CONTAIN(Select(level.tests.structs, ::delegateStructInt), 30);
}

test_Range()
{
	EXPECT_EQ(Range(level.tests.ints, 0, 2).size, 2);
	EXPECT_EQ(Range(level.tests.strings, 0, 2).size, 2);
	EXPECT_EQ(Range(level.tests.vectors, 0, 2).size, 2);
}

test_Repeat()
{
	EXPECT_EQ(Repeat(level.tests.ints, 2).size, 20);
	EXPECT_EQ(Repeat(level.tests.strings, 2).size, 10);
	EXPECT_EQ(Repeat(level.tests.vectors, 2).size, 20);
}

test_Reverse()
{
	EXPECT_EQ(Reverse(level.tests.ints)[0], 9);
	EXPECT_EQ(Reverse(level.tests.strings)[0], "10");
	EXPECT_EQ(Reverse(level.tests.vectors)[0], (9.45, 9.45, 9.45));
}

test_Remove()
{
	EXPECT_EQ(Remove(level.tests.ints, 0).size, 9);
}

test_RemoveAt()
{
	EXPECT_EQ(RemoveAt(level.tests.ints, 0).size, 9);
}

test_PmFlags()
{
	EXPECT_EQ(level.gscunit.bots[0] PmFlags(), 0);
}

test_PmTime()
{
	EXPECT_EQ(level.gscunit.bots[0] PmTime(), 0);
}

test_PmType()
{
	EXPECT_EQ(level.gscunit.bots[0] PmType(), 0);
}

test_WeaponFlags()
{
	EXPECT_EQ(level.gscunit.bots[0] WeaponFlags(), 0);
}

test_fmod()
{
	EXPECT_EQ(fmod(9, 2), 1);
	EXPECT_EQ(fmod(4, 2), 0);
}

test_tan1()
{
	EXPECT_EQ(tan1(0.9), 1.260158);
	EXPECT_EQ(tan1(0.4), 0.422793);
}

test_atan1()
{
	EXPECT_EQ(atan1(0.9), 0.732815);
	EXPECT_EQ(atan1(0.4), 0.380506);
}

test_atan2()
{
	EXPECT_EQ(atan2(9, 2), 1.352127);
	EXPECT_EQ(atan2(4, 2), 1.107149);
}

test_cos1()
{
	EXPECT_EQ(cos1(0.9), 0.621610);
	EXPECT_EQ(cos1(0.4), 0.921061);
}

test_acos1()
{
	EXPECT_EQ(acos1(0.9), 0.451027);
	EXPECT_EQ(acos1(0.4), 1.159279);
}

test_sin1()
{
	EXPECT_EQ(sin1(0.9), 0.783327);
	EXPECT_EQ(sin1(0.4), 0.389418);
}

test_asin1()
{
	EXPECT_EQ(asin1(0.9), 1.119769);
	EXPECT_EQ(asin1(0.4), 0.411517);
}

test_GetRightMove()
{
	EXPECT_EQ(level.gscunit.bots[0] GetRightMove(), 0);
}

test_GetForwardMove()
{
	EXPECT_EQ(level.gscunit.bots[0] GetForwardMove(), 0);
}

test_GetIP()
{
	EXPECT_EQ(level.gscunit.bots[0] GetIP(), "bot");
}

test_Replace()
{
	EXPECT_EQ(Replace("SR Speedrun", "Speedrun", "Deathrun"), "SR Deathrun");
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
	EXPECT_EQ(ToString(2.2), "2.2");
	EXPECT_EQ(ToString((3.3, 3.3, 3.3)), "(3.3, 3.3, 3.3)");
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
