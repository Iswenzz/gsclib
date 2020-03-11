// Main tests
test()
{
    wait 10;

    thread gsclinq_tests();
    thread data_structs_tests();
}

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
        //printResultArray(isAll);

        wait 5;
    }
}

gsclinq_tests()
{
    arr = [];
    for (i = 0; i < 10; i++)
        arr[i] = i;

    // All
    comPrintF("\n[TEST] GSC-Linq - All \n");
    printResultArray(all(arr, arr.size, ::testPredicate));

    // Any
    comPrintF("\n[TEST] GSC-Linq - Any \n");
    printResultArray(any(arr, arr.size, ::testPredicate));

    // Where
    comPrintF("\n[TEST] GSC-Linq - Where \n");
    printArray(where(arr, arr.size, ::testPredicate));

    // Min
    comPrintF("\n[TEST] GSC-Linq - Min \n");
    //printResultArray(min(arr, arr.size));

    // Max
    comPrintF("\n[TEST] GSC-Linq - Max \n");
    //printResultArray(max(arr, arr.size));

    // First
    comPrintF("\n[TEST] GSC-Linq - First \n");
    printResultArray(first(arr, arr.size, ::testPredicate));

    // Last
    comPrintF("\n[TEST] GSC-Linq - Last \n");
    printResultArray(last(arr, arr.size, ::testPredicate));

    // Cast
    comPrintF("\n[TEST] GSC-Linq - Cast \n");
    //printResultArray(cast(arr, arr.size, "string"));

    // OrderBy
    comPrintF("\n[TEST] GSC-Linq - OrderBy \n");
    //printResult(orderBy(arr, arr.size, ::testPredicate));

    // Average
    comPrintF("\n[TEST] GSC-Linq - Average \n");
    printResultArray(average(arr, arr.size));

    // Count
    comPrintF("\n[TEST] GSC-Linq - Count \n");
    printResultArray(count(arr, arr.size, ::testPredicate));

    // Sum
    comPrintF("\n[TEST] GSC-Linq - Sum \n");
    printResultArray(sum(arr, arr.size));

    // Select
    comPrintF("\n[TEST] GSC-Linq - Select \n");
    //printResultArray(select(arr, arr.size, ::testPredicate));
    
    // Range
    comPrintF("\n[TEST] GSC-Linq - Range \n");
    printArray(range(arr, arr.size, 0, 2));

    // Repeat
    comPrintF("\n[TEST] GSC-Linq - Repeat \n");
    printArray(repeat(arr, arr.size, 2));

    // Reverse
    comPrintF("\n[TEST] GSC-Linq - Reverse \n");
    printArray(reverse(arr, arr.size));
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

// Print all items in array
printArray(arr)
{
    if (isDefined(arr) && isDefined(arr.size))
    {
        for (i = 0; i < arr.size; i++)
        {
            iprintlnbold("" + arr[i]);
            comPrintf("" + arr[i] + "\n");
        }
    }
}

// Print variable
printResultArray(result)
{
    iprintlnbold("" + result);
    comPrintf("" + result + "\n");
}

// Test predicate
testPredicate(item)
{
    return item != 5;
}
