// Main tests
test()
{
    wait 10;

    thread gsclinq_tests();
    thread data_structs_tests();
}

// tests for gsclib/collections
data_structs_tests()
{
    arr = [];
    for (i = 0; i < 10; i++)
        arr[i] = i;

    while (true)
    {
        tlist = ListNew();
        //ListAdd(tlist, 600);
        //ListAdd(tlist, 300);
        //comPrintF("Get: " + ListGet(tlist, 0) + "\n");
        //comPrintF("Length: " + ListLength(tlist) + "\n");
        //ListInsert(tlist, 400, 1);
        //comPrintF("Insert: " + ListGet(tlist, 1) + "\n");
        //ListRemove(tlist, 600);
        //comPrintF("Remove: " + ListGet(tlist, 0) + "\n");
        
        //testxd(arr, 400, 800);
        //array = repeat(arr, arr.size, 2);
        
        //array = listAdd(arr, arr.size, 200);
        //printNewArray(array);

        //isAll = count(arr, arr.size, ::testPredicate);
        //printVariableWithType(isAll);

        wait 5;
    }
}

// Tests for gsclib/linq
gsclinq_tests()
{
    arr = [];
    for (i = 0; i < 10; i++)
        arr[i] = i;

    arr2 = [];
    arr2[arr2.size] = "a";
    arr2[arr2.size] = "10";
    arr2[arr2.size] = "abc 1 ac";
    arr2[arr2.size] = "b2";

    arr3 = [];
    for (i = 0; i < 10; i++)
        arr3[i] = i * 1.05;
    
    // All
    comPrintF("\n[TEST] GSC-Linq - All \n");
    printVariableWithType(all(arr, arr.size, ::testPredicate));

    // Any
    comPrintF("\n[TEST] GSC-Linq - Any \n");
    printVariableWithType(any(arr, arr.size, ::testPredicate));

    // Where
    comPrintF("\n[TEST] GSC-Linq - Where \n");
    printArrayWithType(where(arr, arr.size, ::testPredicate));

    // Min & Max
    comPrintF("\n[TEST] GSC-Linq - Min \n");
    printVariableWithType(min(arr, arr.size));
    printVariableWithType(min(arr2, arr2.size));
    comPrintF("\n[TEST] GSC-Linq - Max \n");
    printVariableWithType(max(arr, arr.size));
    printVariableWithType(max(arr2, arr2.size));

    // First
    comPrintF("\n[TEST] GSC-Linq - First \n");
    printVariableWithType(first(arr, arr.size, ::testPredicate));

    // Last
    comPrintF("\n[TEST] GSC-Linq - Last \n");
    printVariableWithType(last(arr, arr.size, ::testPredicate));

    // Cast
    comPrintF("\n[TEST] GSC-Linq - Cast \n");
    cast_arr = [];
    cast_arr[cast_arr.size] = "100";
    cast_arr[cast_arr.size] = 200;
    cast_arr[cast_arr.size] = 300.300;
    printArrayWithType(cast(cast_arr, cast_arr.size, "string"));
    printArrayWithType(cast(cast_arr, cast_arr.size, "int"));
    printArrayWithType(cast(cast_arr, cast_arr.size, "float"));

    // OrderBy
    comPrintF("\n[TEST] GSC-Linq - OrderBy \n");
    //printResult(orderBy(arr, arr.size, ::testPredicate));

    // Average
    comPrintF("\n[TEST] GSC-Linq - Average \n");
    printVariableWithType(average(arr, arr.size));

    // Count
    comPrintF("\n[TEST] GSC-Linq - Count \n");
    printVariableWithType(count(arr, arr.size, ::testPredicate));

    // Sum
    comPrintF("\n[TEST] GSC-Linq - Sum \n");
    printVariableWithType(sum(arr, arr.size));

    // Select
    comPrintF("\n[TEST] GSC-Linq - Select \n");
    //printVariableWithType(select(arr, arr.size, ::testPredicate));
    
    // Range
    comPrintF("\n[TEST] GSC-Linq - Range \n");
    printArrayWithType(range(arr, arr.size, 0, 2));

    // Repeat
    comPrintF("\n[TEST] GSC-Linq - Repeat \n");
    printArrayWithType(repeat(arr, arr.size, 2));

    // Reverse
    comPrintF("\n[TEST] GSC-Linq - Reverse \n");
    printArrayWithType(reverse(arr, arr.size));
}

// Main tests on player ent
testPlayer()
{
    wait 5;

    arr = [];
    for (i = 0; i < 10; i++)
        arr[i] = self;

    while (true)
    {
        wait 5;
    }
}

// Print all items in the array with their type.
printArrayWithType(arr)
{
    if (isDefined(arr) && isDefined(arr.size))
    {
        for (i = 0; i < arr.size; i++)
        {
            msg = "" + arr[i] + " " + GetType(arr[i]);
            iprintlnbold(msg);
            comPrintf(msg + "\n");
        }
    }
}

// Print all items in the array
printArray(arr)
{
    if (isDefined(arr) && isDefined(arr.size))
    {
        for (i = 0; i < arr.size; i++)
        {
            msg = "" + arr[i];
            iprintlnbold(msg);
            comPrintf(msg + "\n");
        }
    }
}

// Print variable
printVariable(var)
{
    msg = "" + var;
    iprintlnbold(msg);
    comPrintf(msg + "\n");
}

// Print variable with its type
printVariableWithType(var)
{
    msg = "" + var + " " + GetType(var);
    iprintlnbold(msg);
    comPrintf(msg + "\n");
}

// Test predicate
testPredicate(item)
{
    return item != 5;
}
