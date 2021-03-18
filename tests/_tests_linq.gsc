#include sr\tests\gsclib\_main;

// Tests for gsclib/linq
test(loop)
{
	comPrintF("\n[======{Linq}======]\n");

	// float array
	level._tests_floats = [];
	for (i = 0; i < 10; i++)
		level._tests_floats[i] = i * 1.05;

	// int array
	level._tests_ints = [];
	for (i = 0; i < 10; i++)
		level._tests_ints[i] = i;

	// string array
	level._tests_strings = strTok("Ellin;Alexa;Celiza;Iswenzz;10", ";");

	// vector array
	level._tests_vectors = [];
	for (i = 0; i < 10; i++)
		level._tests_vectors[i] = (level._tests_floats[i], level._tests_floats[i], level._tests_floats[i]);

	// struct array
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

	// 2dim array
	level._tests_arrays = [];
	level._tests_arrays[level._tests_arrays.size] = level._tests_floats;
	level._tests_arrays[level._tests_arrays.size] = level._tests_ints;
	level._tests_arrays[level._tests_arrays.size] = level._tests_vectors;
	level._tests_arrays[level._tests_arrays.size] = level._tests_structs;

	// ent array
	level._tests_ents = getEntArray("player", "classname");

	while (true)
	{
		it_all();
		it_any();
		it_where();
		it_getmin();
		it_getmax();
		it_last();
		it_first();
		it_cast();
		it_oftype();
		it_sort();
		it_average();
		it_count();
		it_sum();
		it_select();
		it_range();
		it_repeat();
		it_reverse();

		if (!loop)
			break;
		wait 0.05;
	}
}

it_all()
{
	comPrintF("\n<-------[All]------->\n");
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
	comPrintF("\n<-------[Any]------->\n");
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
	comPrintF("\n<-------[Where]------->\n");
	printArrayWithType(where(level._tests_ints, ::testPredicate));
	comPrintF();
	printArrayWithType(where(level._tests_strings, ::testPredicateString));
	comPrintF();
	printArrayWithType(where(level._tests_vectors, ::testPredicateVector));
}

it_getmin()
{
	comPrintF("\n<-------[Min]------->\n");
	printVariableWithType(getMin(level._tests_ints));
	comPrintF();
	printVariableWithType(getMin(level._tests_strings));
	comPrintF();
	printVariableWithType(getMin(level._tests_vectors));
}

it_getmax()
{
	comPrintF("\n<-------[Max]------->\n");
	printVariableWithType(getMax(level._tests_ints));
	comPrintF();
	printVariableWithType(getMax(level._tests_strings));
	comPrintF();
	printVariableWithType(getMax(level._tests_vectors));
}

it_last()
{
	comPrintF("\n<-------[Last]------->\n");
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
	comPrintF("\n<-------[First]------->\n");
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
	comPrintF("\n<-------[Cast]------->\n");

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
	comPrintF("\n<-------[OfType]------->\n");

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
	comPrintF("\n<-------[Sort]------->\n");
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
	comPrintF("\n<-------[Average]------->\n");
	printVariableWithType(average(level._tests_ints));
	comPrintF();
	printVariableWithType(average(level._tests_vectors));
}

it_count()
{
	comPrintF("\n<-------[Count]------->\n");
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
	comPrintF("\n<-------[Sum]------->\n");
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
	comPrintF("\n<-------[Select]------->\n");

	printArrayWithType(select(level._tests_structs, ::testDelegateStructString));
	comPrintF();
	printArrayWithType(select(level._tests_structs, ::testDelegateStructInt));
}

it_range()
{
	comPrintF("\n<-------[Range]------->\n");
	printArrayWithType(range(level._tests_ints, 0, 2));
	comPrintF();
	printArrayWithType(range(level._tests_strings, 0, 2));
	comPrintF();
	printArrayWithType(range(level._tests_vectors, 0, 2));
}

it_repeat()
{
	comPrintF("\n<-------[Repeat]------->\n");
	printArrayWithType(repeat(level._tests_ints, 2));
	comPrintF();
	printArrayWithType(repeat(level._tests_strings, 2));
	comPrintF();
	printArrayWithType(repeat(level._tests_vectors, 2));
}

it_reverse()
{
	comPrintF("\n<-------[Reverse]------->\n");
	printArrayWithType(reverse(level._tests_ints));
	comPrintF();
	printArrayWithType(reverse(level._tests_strings));
	comPrintF();
	printArrayWithType(reverse(level._tests_vectors));
}
