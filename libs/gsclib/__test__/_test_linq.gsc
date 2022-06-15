#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Linq");

	// linq/delegates
	it(::test_Select, "Select");
	it(::test_Foreach, "Foreach");
	it(::test_Aggregate, "Aggregate");

	// linq/enumerables
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
	it(::test_IndexOf, "IndexOf");
	it(::test_Remove, "Remove");
	it(::test_RemoveAt, "RemoveAt");

	// linq/predicates
	it(::test_All, "All");
	it(::test_Any, "Any");
	it(::test_Where, "Where");
	it(::test_Last, "Last");
	it(::test_First, "First");
	it(::test_Count, "Count");
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
	EXPECT_CONTAIN(Cast(casts, "string"), "300.299988");
	EXPECT_CONTAIN(Cast(casts, "string"), "(400.000000, 400.000000, 400.000000)");

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
