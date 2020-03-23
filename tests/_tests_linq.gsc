#include lib\gsclib\_main;

// Tests for gsclib/linq
test()
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
    level._tests_structs[0].name = "AK47";
    level._tests_structs[0].weapon = "ak47_mp";
    level._tests_structs[0].bullet = 30;
    level._tests_structs[1] = SpawnStruct();
    level._tests_structs[1].name = "Desert Eagle";
    level._tests_structs[1].weapon = "deserteagle_mp";
    level._tests_structs[1].bullet = 12;
    level._tests_structs[2] = SpawnStruct();
    level._tests_structs[2].name = "M1014";
    level._tests_structs[2].weapon = "m1014_mp";
    level._tests_structs[2].bullet = 8;

    // 2dim array
    level._tests_arrays = [];
    level._tests_arrays[level._tests_arrays.size] = level._tests_floats;
    level._tests_arrays[level._tests_arrays.size] = level._tests_ints;
    level._tests_arrays[level._tests_arrays.size] = level._tests_vectors;
    level._tests_arrays[level._tests_arrays.size] = level._tests_structs;

    // ent array
    level._tests_ents = getEntArray("player", "classname");

    it_all();
    it_any();
    it_where();
    it_min();
    it_max();
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
}

it_all()
{
    comPrintF("\n<-------[All]------->\n");
    printVariableWithType(all(level._tests_ints, level._tests_ints.size, ::testPredicate));
    comPrintF();
    printVariableWithType(all(level._tests_strings, level._tests_strings.size, ::testPredicateString));
    comPrintF();
    printVariableWithType(all(level._tests_vectors, level._tests_vectors.size, ::testPredicateVector));
    comPrintF();
    printVariableWithType(all(level._tests_structs, level._tests_structs.size, ::testPredicateName));
    comPrintF();
    printVariableWithType(all(level._tests_arrays, level._tests_arrays.size, ::testPredicateArray));
    comPrintF();
    printVariableWithType(all(level._tests_ents, level._tests_ents.size, ::testPredicateEnt));
}

it_any()
{
    comPrintF("\n<-------[Any]------->\n");
    printVariableWithType(any(level._tests_ints, level._tests_ints.size, ::testPredicate));
    comPrintF();
    printVariableWithType(any(level._tests_strings, level._tests_strings.size, ::testPredicateString));
    comPrintF();
    printVariableWithType(any(level._tests_vectors, level._tests_vectors.size, ::testPredicateVector));
    comPrintF();
    printVariableWithType(any(level._tests_structs, level._tests_structs.size, ::testPredicateName));
    comPrintF();
    printVariableWithType(any(level._tests_arrays, level._tests_arrays.size, ::testPredicateArray));
}

it_where()
{
    comPrintF("\n<-------[Where]------->\n");
    printArrayWithType(where(level._tests_ints, level._tests_ints.size, ::testPredicate));
    comPrintF();
    printArrayWithType(where(level._tests_strings, level._tests_strings.size, ::testPredicateString));
    comPrintF();
    printArrayWithType(where(level._tests_vectors, level._tests_vectors.size, ::testPredicateVector));
}

it_min()
{
    comPrintF("\n<-------[Min]------->[\n");
    printVariableWithType(min(level._tests_ints, level._tests_ints.size));
    comPrintF();
    printVariableWithType(min(level._tests_strings, level._tests_strings.size));
    comPrintF();
    printVariableWithType(min(level._tests_vectors, level._tests_vectors.size));
}

it_max()
{
    comPrintF("\n<-------[Max]------->\n");
    printVariableWithType(max(level._tests_ints, level._tests_ints.size));
    comPrintF();
    printVariableWithType(max(level._tests_strings, level._tests_strings.size));
    comPrintF();
    printVariableWithType(max(level._tests_vectors, level._tests_vectors.size));
}

it_last()
{
    comPrintF("\n<-------[Last]------->\n");
    printVariableWithType(last(level._tests_ints, level._tests_ints.size, ::testPredicate));
    comPrintF();
    printVariableWithType(last(level._tests_strings, level._tests_strings.size, ::testPredicateString));
    comPrintF();
    printVariableWithType(last(level._tests_vectors, level._tests_vectors.size, ::testPredicateVector));
    comPrintF();
    printVariableWithType(last(level._tests_structs, level._tests_structs.size, ::testPredicateName).name);
    comPrintF();
    printVariableWithType(last(level._tests_arrays, level._tests_arrays.size, ::testPredicateArray)[0].name);
    comPrintF();
    printVariableWithType(last(level._tests_ents, level._tests_ents.size, ::testPredicateEnt).name);
}

it_first()
{
    comPrintF("\n<-------[First]------->\n");
    printVariableWithType(first(level._tests_ints, level._tests_ints.size, ::testPredicate));
    comPrintF();
    printVariableWithType(first(level._tests_strings, level._tests_strings.size, ::testPredicateString));
    comPrintF();
    printVariableWithType(first(level._tests_vectors, level._tests_vectors.size, ::testPredicateVector));
    comPrintF();
    printVariableWithType(first(level._tests_structs, level._tests_structs.size, ::testPredicateName).name);
    comPrintF();
    printVariableWithType(first(level._tests_ents, level._tests_ents.size, ::testPredicateEnt).name);
}

it_cast()
{
    comPrintF("\n<-------[Cast]------->\n");

    cast_arr = [];
    cast_arr[cast_arr.size] = "100";
    cast_arr[cast_arr.size] = 200;
    cast_arr[cast_arr.size] = 300.300;
    cast_arr[cast_arr.size] = (400, 400, 400);

    printArrayWithType(cast(cast_arr, cast_arr.size, "string"));
    comPrintF();
    printArrayWithType(cast(cast_arr, cast_arr.size, "int"));
    comPrintF();
    printArrayWithType(cast(cast_arr, cast_arr.size, "float"));
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

    printArrayWithType(ofType(cast_arr, cast_arr.size, "string"));
    comPrintF();
    printArrayWithType(ofType(cast_arr, cast_arr.size, "int"));
    comPrintF();
    printArrayWithType(ofType(cast_arr, cast_arr.size, "float"));
    comPrintF();
    printArrayWithType(ofType(cast_arr, cast_arr.size, "vector"));
    comPrintF();
    printVariableWithType(ofType(cast_arr, cast_arr.size, "struct")[0].name);
    comPrintF();
    printArrayWithType(ofType(cast_arr, cast_arr.size, "array")[0]);
    comPrintF();
    printVariableWithType(ofType(cast_arr, cast_arr.size, "ent")[0].name);
}

it_sort()
{
    comPrintF("\n<-------[Sort]------->\n");
    printArrayWithType(sort(level._tests_ints, level._tests_ints.size));
    comPrintF();
    printArrayWithType(sort(level._tests_floats, level._tests_floats.size));
    comPrintF();
    printArrayWithType(sort(level._tests_strings, level._tests_strings.size));
    comPrintF();
    printArrayWithType(sort(level._tests_vectors, level._tests_vectors.size));
}

it_average()
{
    comPrintF("\n<-------[Average]------->\n");
    printVariableWithType(average(level._tests_ints, level._tests_ints.size));
    comPrintF();
    printVariableWithType(average(level._tests_vectors, level._tests_vectors.size));
}

it_count()
{
    comPrintF("\n<-------[Count]------->\n");
    printVariableWithType(count(level._tests_ints, level._tests_ints.size, ::testPredicate));
    comPrintF();
    printVariableWithType(count(level._tests_floats, level._tests_floats.size, ::testPredicate));
    comPrintF();
    printVariableWithType(count(level._tests_strings, level._tests_strings.size, ::testPredicateString));
    comPrintF();
    printVariableWithType(count(level._tests_vectors, level._tests_vectors.size, ::testPredicateVector));
    comPrintF();
    printVariableWithType(count(level._tests_structs, level._tests_structs.size, ::testPredicateName));
    comPrintF();
    printVariableWithType(count(level._tests_arrays, level._tests_arrays.size, ::testPredicateArray));
}

it_sum()
{
    comPrintF("\n<-------[Sum]------->\n");
    printVariableWithType(sum(level._tests_ints, level._tests_ints.size));
    comPrintF();
    printVariableWithType(sum(level._tests_floats, level._tests_floats.size));
    comPrintF();
    printVariableWithType(sum(level._tests_strings, level._tests_strings.size));
    comPrintF();
    printVariableWithType(sum(level._tests_vectors, level._tests_vectors.size));
}

it_select()
{
    comPrintF("\n<-------[Select]------->\n");
    comPrintF("Not implemented yet.\n");
    // printArrayWithType(select(level._tests_structs, level._tests_structs.size, ::testDelegateName));
    // comPrintF();
    //printArrayWithType(select(level._tests_structs, level._tests_structs.size, ::testDelegateBullet));
}

it_range()
{
    comPrintF("\n<-------[Range]------->\n");
    printArrayWithType(range(level._tests_ints, level._tests_ints.size, 0, 2));
    comPrintF();
    printArrayWithType(range(level._tests_strings, level._tests_strings.size, 0, 2));
    comPrintF();
    printArrayWithType(range(level._tests_vectors, level._tests_vectors.size, 0, 2));
}

it_repeat()
{
    comPrintF("\n<-------[Repeat]------->\n");
    printArrayWithType(repeat(level._tests_ints, level._tests_ints.size, 2));
    comPrintF();
    printArrayWithType(repeat(level._tests_strings, level._tests_strings.size, 2));
    comPrintF();
    printArrayWithType(repeat(level._tests_vectors, level._tests_vectors.size, 2));
}

it_reverse()
{
    comPrintF("\n<-------[Reverse]------->\n");
    printArrayWithType(reverse(level._tests_ints, level._tests_ints.size));
    comPrintF();
    printArrayWithType(reverse(level._tests_strings, level._tests_strings.size));
    comPrintF();
    printArrayWithType(reverse(level._tests_vectors, level._tests_vectors.size));
}
