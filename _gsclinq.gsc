printNewArray(arr)
{
    if (isDefined(arr) && isDefined(arr.size))
    {
        for (i = 0; i < arr.size; i++)
        {
            iprintlnbold("" + arr[i]);
            comPrintf("" + arr[i] + "\n");
        }
        comPrintf("\n");
    }
}

printResultArray(result)
{
    iprintlnbold("" + result);
    comPrintf("" + result + "\n");
}

testPredicate(item)
{
    return item != 5;
}

test()
{
    wait 10;

    arr = [];
    for (i = 0; i < 10; i++)
        arr[i] = i;

    comprintf("test func\n");

    while (true)
    {
        //array = repeat(arr, arr.size, 2);
        //printNewArray(array);

        isAll = count(arr, arr.size, ::testPredicate);
        printResultArray(isAll);
        wait 5;
    }
}

testPlayer()
{
    wait 5;

    arr = [];
    for (i = 0; i < 10; i++)
        arr[i] = self;

    // while (true)
    // {
    //     self extest();
    //     // array = where(arr, arr.size, ::testPredicate);
    //     // printNewArray(array);

    //     wait 5;
    // }
}

max(array)
{
    value = array[0];
    for (i = 0; i < array.size; i++)
    {
        if (array[i] > value)
            value = array[i];
    }
    return value;
}

min(array)
{
    value = array[0];
    for (i = 0; i < array.size; i++)
    {
        if (array[i] < value)
            value = array[i];
    }
    return value;
}
