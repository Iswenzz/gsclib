#include libs\gscunit\_main;
#include libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB - Linq");
	setup();

	// linq/delegates
	it(::test_Select, "Select");
	it(::test_Foreach, "Foreach");

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

	// linq/predicates
	it(::test_All, "All");
	it(::test_Any, "Any");
	it(::test_Where, "Where");
	it(::test_Last, "Last");
	it(::test_First, "First");
	it(::test_Count, "Count");
}

setup()
{
	// Float array
	level.tests.floats = [];
	for (i = 0; i < 10; i++)
		level.tests.floats[i] = i * 1.05;

	// Int array
	level.tests.ints = [];
	for (i = 0; i < 10; i++)
		level.tests.ints[i] = i;

	// String array
	level.tests.strings = strTok("Ellin;Alexa;Celiza;Iswenzz;10", ";");

	// Vector array
	level.tests.vectors = [];
	for (i = 0; i < 10; i++)
		level.tests.vectors[i] = (level.tests.floats[i], level.tests.floats[i], level.tests.floats[i]);

	// Struct array
	level.tests.structs = [];
	level.tests.structs[0] = SpawnStruct();
	level.tests.structs[0].string = "AK47";
	level.tests.structs[0].int = 30;
	level.tests.structs[0].vector = (100, 200, 300);
	level.tests.structs[0].array = level.tests.ints;
	level.tests.structs[0].float = 1.5;
	level.tests.structs[1] = SpawnStruct();
	level.tests.structs[1].string = "Desert Eagle";
	level.tests.structs[1].int = 12;
	level.tests.structs[1].vector = (400, 500, 600);
	level.tests.structs[1].array = level.tests.floats;
	level.tests.structs[1].float = 2.5;
	level.tests.structs[2] = SpawnStruct();
	level.tests.structs[2].string = "M1014";
	level.tests.structs[2].int = 8;
	level.tests.structs[2].vector = (700, 800, 900);
	level.tests.structs[2].array = level.tests.strings;
	level.tests.structs[2].float = 3.5;

	// 2D array
	level.tests.arrays = [];
	level.tests.arrays[level.tests.arrays.size] = level.tests.floats;
	level.tests.arrays[level.tests.arrays.size] = level.tests.ints;
	level.tests.arrays[level.tests.arrays.size] = level.tests.vectors;
	level.tests.arrays[level.tests.arrays.size] = level.tests.structs;

	// Ent array
	level.tests.ents = getEntArray("player", "classname");
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
	EXPECT_EQ(all(level.tests.ints, ::predicate), false);
	EXPECT_EQ(all(level.tests.strings, ::predicateString), false);
	EXPECT_EQ(all(level.tests.vectors, ::predicateVector), false);
	EXPECT_EQ(all(level.tests.structs, ::predicateStructString), false);
	EXPECT_EQ(all(level.tests.arrays, ::predicateArray), false);
	EXPECT_EQ(all(level.tests.ents, ::predicateEnt), true);
}

test_Any()
{
	EXPECT_EQ(any(level.tests.ints, ::predicate), true);
	EXPECT_EQ(any(level.tests.strings, ::predicateString), true);
	EXPECT_EQ(any(level.tests.vectors, ::predicateVector), true);
	EXPECT_EQ(any(level.tests.structs, ::predicateStructString), true);
	EXPECT_EQ(any(level.tests.arrays, ::predicateArray), true);
}

test_Where()
{
	EXPECT_NOT_CONTAIN(where(level.tests.ints, ::predicate), 5);
	EXPECT_NOT_CONTAIN(where(level.tests.strings, ::predicateString), "Iswenzz");
	EXPECT_NOT_CONTAIN(where(level.tests.vectors, ::predicateVector), (0, 0, 0));
}

test_GetMin()
{
	EXPECT_EQ(getMin(level.tests.ints), 0);
	EXPECT_EQ(getMin(level.tests.strings), "10");
	EXPECT_EQ(getMin(level.tests.vectors), (0, 0, 0));
}

test_GetMax()
{
	EXPECT_EQ(getMax(level.tests.ints), 9);
	EXPECT_EQ(getMax(level.tests.strings), "Iswenzz");
	EXPECT_EQ(getMax(level.tests.vectors), (9.45, 9.45, 9.45));
}

test_Last()
{
	EXPECT_EQ(last(level.tests.ints, ::predicate), 9);
	EXPECT_EQ(last(level.tests.strings, ::predicateString), "10");
	EXPECT_EQ(last(level.tests.vectors, ::predicateVector), (9.45, 9.45, 9.45));
	EXPECT_EQ(last(level.tests.structs, ::predicateStructString).string, "Desert Eagle");
	EXPECT_EQ(last(level.tests.arrays, ::predicateArray)[0].string, "AK47");
	EXPECT_CONTAIN(last(level.tests.ents, ::predicateEnt).name, "bot");
}

test_First()
{
	EXPECT_EQ(first(level.tests.ints, ::predicate), 0);
	EXPECT_EQ(first(level.tests.strings, ::predicateString), "Ellin");
	EXPECT_EQ(first(level.tests.vectors, ::predicateVector), (1.05, 1.05, 1.05));
	EXPECT_EQ(first(level.tests.structs, ::predicateStructString).string, "AK47");
	EXPECT_EQ(first(level.tests.arrays, ::predicateArray)[0].string, "AK47");
	EXPECT_CONTAIN(first(level.tests.ents, ::predicateEnt).name, "bot");
}

test_Cast()
{
	casts = [];
	casts[casts.size] = "100";
	casts[casts.size] = 200;
	casts[casts.size] = 300.300;
	casts[casts.size] = (400, 400, 400);

	EXPECT_CONTAIN(cast(casts, "string"), "100");
	EXPECT_CONTAIN(cast(casts, "string"), "200");
	EXPECT_CONTAIN(cast(casts, "string"), "300.299988");
	EXPECT_CONTAIN(cast(casts, "string"), "(400.000000, 400.000000, 400.000000)");

	EXPECT_CONTAIN(cast(casts, "int"), 100);
	EXPECT_CONTAIN(cast(casts, "int"), 200);
	EXPECT_CONTAIN(cast(casts, "int"), 300);

	EXPECT_CONTAIN(cast(casts, "float"), 100);
	EXPECT_CONTAIN(cast(casts, "float"), 200);
	EXPECT_CONTAIN(cast(casts, "float"), 300.3);
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

	EXPECT_EQ(ofType(vars, "string").size, 1);
	EXPECT_EQ(ofType(vars, "int").size, 1);
	EXPECT_EQ(ofType(vars, "float").size, 1);
	EXPECT_EQ(ofType(vars, "vector").size, 1);

	EXPECT_EQ(ofType(vars, "struct")[0].string, "AK47");
	EXPECT_EQ(ofType(vars, "array")[0].size, 10);
	EXPECT_CONTAIN(ofType(vars, "ent")[0].name, "bot");
}

test_Sort()
{
	EXPECT_EQ(sort(level.tests.ints)[0], 0);
	EXPECT_EQ(sort(level.tests.floats)[0], 0);
	EXPECT_EQ(sort(level.tests.strings)[0], "10");
	EXPECT_EQ(sort(level.tests.vectors)[0], (1.05, 1.05, 1.05));
}

test_Average()
{
	EXPECT_EQ(average(level.tests.ints), 4.5);
	EXPECT_EQ(average(level.tests.vectors), (4.725, 4.725, 4.725));
}

test_Count()
{
	EXPECT_EQ(count(level.tests.ints, ::predicate), 9);
	EXPECT_EQ(count(level.tests.floats, ::predicate), 10);
	EXPECT_EQ(count(level.tests.strings, ::predicateString), 4);
	EXPECT_EQ(count(level.tests.vectors, ::predicateVector), 9);
	EXPECT_EQ(count(level.tests.structs, ::predicateStructString), 2);
	EXPECT_EQ(count(level.tests.arrays, ::predicateArray), 1);
}

test_Sum()
{
	EXPECT_EQ(sum(level.tests.ints), 45);
	EXPECT_EQ(sum(level.tests.floats), 47.25);
	EXPECT_EQ(sum(level.tests.strings), "EllinAlexaCelizaIswenzz10");
	EXPECT_EQ(sum(level.tests.vectors), (47.25, 47.25, 47.25));
}

test_Select()
{
	EXPECT_CONTAIN(select(level.tests.structs, ::delegateStructString), "AK47");
	EXPECT_CONTAIN(select(level.tests.structs, ::delegateStructInt), 30);
}

test_Range()
{
	EXPECT_EQ(range(level.tests.ints, 0, 2).size, 2);
	EXPECT_EQ(range(level.tests.strings, 0, 2).size, 2);
	EXPECT_EQ(range(level.tests.vectors, 0, 2).size, 2);
}

test_Repeat()
{
	EXPECT_EQ(repeat(level.tests.ints, 2).size, 20);
	EXPECT_EQ(repeat(level.tests.strings, 2).size, 10);
	EXPECT_EQ(repeat(level.tests.vectors, 2).size, 20);
}

test_Reverse()
{
	EXPECT_EQ(reverse(level.tests.ints)[0], 9);
	EXPECT_EQ(reverse(level.tests.strings)[0], "10");
	EXPECT_EQ(reverse(level.tests.vectors)[0], (9.45, 9.45, 9.45));
}
