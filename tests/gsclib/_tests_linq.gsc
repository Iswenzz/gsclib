#include sr\tests\_main;
#include sr\tests\gsclib\_main;

// Tests for gsclib/linq
test()
{
	suit("GSCLIB - Linq");

	// Float array
	level._tests_floats = [];
	for (i = 0; i < 10; i++)
		level._tests_floats[i] = i * 1.05;

	// Int array
	level._tests_ints = [];
	for (i = 0; i < 10; i++)
		level._tests_ints[i] = i;

	// String array
	level._tests_strings = strTok("Ellin;Alexa;Celiza;Iswenzz;10", ";");

	// Vector array
	level._tests_vectors = [];
	for (i = 0; i < 10; i++)
		level._tests_vectors[i] = (level._tests_floats[i], level._tests_floats[i], level._tests_floats[i]);

	// Struct array
	level._tests_structs = [];
	level._tests_structs[0] = SpawnStruct();
	level._tests_structs[0].string = "AK47";
	level._tests_structs[0].int = 30;
	level._tests_structs[0].vector = (100, 200, 300);
	level._tests_structs[0].array = level._tests_ints;
	level._tests_structs[0].float = 1.5;
	level._tests_structs[1] = SpawnStruct();
	level._tests_structs[1].string = "Desert Eagle";
	level._tests_structs[1].int = 12;
	level._tests_structs[1].vector = (400, 500, 600);
	level._tests_structs[1].array = level._tests_floats;
	level._tests_structs[1].float = 2.5;
	level._tests_structs[2] = SpawnStruct();
	level._tests_structs[2].string = "M1014";
	level._tests_structs[2].int = 8;
	level._tests_structs[2].vector = (700, 800, 900);
	level._tests_structs[2].array = level._tests_strings;
	level._tests_structs[2].float = 3.5;

	// 2D array
	level._tests_arrays = [];
	level._tests_arrays[level._tests_arrays.size] = level._tests_floats;
	level._tests_arrays[level._tests_arrays.size] = level._tests_ints;
	level._tests_arrays[level._tests_arrays.size] = level._tests_vectors;
	level._tests_arrays[level._tests_arrays.size] = level._tests_structs;

	// Ent array
	level._tests_ents = getEntArray("player", "classname");

	run(::it_all, "All");
	run(::it_any, "Any");
	run(::it_where, "Where");
	run(::it_getmin, "GetMin");
	run(::it_getmax, "GetMax");
	run(::it_last, "Last");
	run(::it_first, "First");
	run(::it_cast, "Cast");
	run(::it_oftype, "OfType");
	run(::it_sort, "Sort");
	run(::it_average, "Average");
	run(::it_count, "Count");
	run(::it_sum, "Sum");
	run(::it_select, "Select");
	run(::it_range, "Range");
	run(::it_repeat, "Repeat");
	run(::it_reverse, "Reverse");
}

it_all()
{
	printVariableWithType(all(level._tests_ints, ::testPredicate));
	comPrintF();
	printVariableWithType(all(level._tests_strings, ::testPredicateString));
	comPrintF();
	printVariableWithType(all(level._tests_vectors, ::testPredicateVector));
	comPrintF();
	printVariableWithType(all(level._tests_structs, ::testPredicateStructString));
	comPrintF();
	printVariableWithType(all(level._tests_arrays, ::testPredicateArray));
	comPrintF();
	printVariableWithType(all(level._tests_ents, ::testPredicateEnt));
}

it_any()
{
	printVariableWithType(any(level._tests_ints, ::testPredicate));
	comPrintF();
	printVariableWithType(any(level._tests_strings, ::testPredicateString));
	comPrintF();
	printVariableWithType(any(level._tests_vectors, ::testPredicateVector));
	comPrintF();
	printVariableWithType(any(level._tests_structs, ::testPredicateStructString));
	comPrintF();
	printVariableWithType(any(level._tests_arrays, ::testPredicateArray));
}

it_where()
{
	printArrayWithType(where(level._tests_ints, ::testPredicate));
	comPrintF();
	printArrayWithType(where(level._tests_strings, ::testPredicateString));
	comPrintF();
	printArrayWithType(where(level._tests_vectors, ::testPredicateVector));
}

it_getmin()
{
	printVariableWithType(getMin(level._tests_ints));
	comPrintF();
	printVariableWithType(getMin(level._tests_strings));
	comPrintF();
	printVariableWithType(getMin(level._tests_vectors));
}

it_getmax()
{
	printVariableWithType(getMax(level._tests_ints));
	comPrintF();
	printVariableWithType(getMax(level._tests_strings));
	comPrintF();
	printVariableWithType(getMax(level._tests_vectors));
}

it_last()
{
	printVariableWithType(last(level._tests_ints, ::testPredicate));
	comPrintF();
	printVariableWithType(last(level._tests_strings, ::testPredicateString));
	comPrintF();
	printVariableWithType(last(level._tests_vectors, ::testPredicateVector));
	comPrintF();
	printVariableWithType(last(level._tests_structs, ::testPredicateStructString).string);
	comPrintF();
	printVariableWithType(last(level._tests_arrays, ::testPredicateArray)[0].string);
	comPrintF();
	printVariableWithType(last(level._tests_ents, ::testPredicateEnt).name);
}

it_first()
{
	printVariableWithType(first(level._tests_ints, ::testPredicate));
	comPrintF();
	printVariableWithType(first(level._tests_strings, ::testPredicateString));
	comPrintF();
	printVariableWithType(first(level._tests_vectors, ::testPredicateVector));
	comPrintF();
	printVariableWithType(first(level._tests_structs, ::testPredicateStructString).string);
	comPrintF();
	printVariableWithType(first(level._tests_arrays, ::testPredicateArray)[0].string);
	comPrintF();
	printVariableWithType(first(level._tests_ents, ::testPredicateEnt).name);
}

it_cast()
{
	cast_arr = [];
	cast_arr[cast_arr.size] = "100";
	cast_arr[cast_arr.size] = 200;
	cast_arr[cast_arr.size] = 300.300;
	cast_arr[cast_arr.size] = (400, 400, 400);

	printArrayWithType(cast(cast_arr, "string"));
	comPrintF();
	printArrayWithType(cast(cast_arr, "int"));
	comPrintF();
	printArrayWithType(cast(cast_arr, "float"));
}

it_oftype()
{
	cast_arr = [];
	cast_arr[cast_arr.size] = "100";
	cast_arr[cast_arr.size] = 200;
	cast_arr[cast_arr.size] = 300.300;
	cast_arr[cast_arr.size] = (400, 400, 400);
	cast_arr[cast_arr.size] = level._tests_structs[0];
	cast_arr[cast_arr.size] = level._tests_ints;
	cast_arr[cast_arr.size] = level._tests_ents[0];

	printArrayWithType(ofType(cast_arr, "string"));
	comPrintF();
	printArrayWithType(ofType(cast_arr, "int"));
	comPrintF();
	printArrayWithType(ofType(cast_arr, "float"));
	comPrintF();
	printArrayWithType(ofType(cast_arr, "vector"));
	comPrintF();
	printVariableWithType(ofType(cast_arr, "struct")[0].string);
	comPrintF();
	printArrayWithType(ofType(cast_arr, "array")[0]);
	comPrintF();
	printVariableWithType(ofType(cast_arr, "ent")[0].string);
}

it_sort()
{
	printArrayWithType(sort(level._tests_ints));
	comPrintF();
	printArrayWithType(sort(level._tests_floats));
	comPrintF();
	printArrayWithType(sort(level._tests_strings));
	comPrintF();
	printArrayWithType(sort(level._tests_vectors));
}

it_average()
{
	printVariableWithType(average(level._tests_ints));
	comPrintF();
	printVariableWithType(average(level._tests_vectors));
}

it_count()
{
	printVariableWithType(count(level._tests_ints, ::testPredicate));
	comPrintF();
	printVariableWithType(count(level._tests_floats, ::testPredicate));
	comPrintF();
	printVariableWithType(count(level._tests_strings, ::testPredicateString));
	comPrintF();
	printVariableWithType(count(level._tests_vectors, ::testPredicateVector));
	comPrintF();
	printVariableWithType(count(level._tests_structs, ::testPredicateStructString));
	comPrintF();
	printVariableWithType(count(level._tests_arrays, ::testPredicateArray));
}

it_sum()
{
	printVariableWithType(sum(level._tests_ints));
	comPrintF();
	printVariableWithType(sum(level._tests_floats));
	comPrintF();
	printVariableWithType(sum(level._tests_strings));
	comPrintF();
	printVariableWithType(sum(level._tests_vectors));
}

it_select()
{
	printArrayWithType(select(level._tests_structs, ::testDelegateStructString));
	comPrintF();
	printArrayWithType(select(level._tests_structs, ::testDelegateStructInt));
}

it_range()
{
	printArrayWithType(range(level._tests_ints, 0, 2));
	comPrintF();
	printArrayWithType(range(level._tests_strings, 0, 2));
	comPrintF();
	printArrayWithType(range(level._tests_vectors, 0, 2));
}

it_repeat()
{
	printArrayWithType(repeat(level._tests_ints, 2));
	comPrintF();
	printArrayWithType(repeat(level._tests_strings, 2));
	comPrintF();
	printArrayWithType(repeat(level._tests_vectors, 2));
}

it_reverse()
{
	printArrayWithType(reverse(level._tests_ints));
	comPrintF();
	printArrayWithType(reverse(level._tests_strings));
	comPrintF();
	printArrayWithType(reverse(level._tests_vectors));
}
