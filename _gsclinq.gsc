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

    while (true)
    {
        array = where(arr, arr.size, ::testPredicate);
        printNewArray(array);
        // printResultArray(array);
        
        // isAll = all(arr, arr.size, ::testPredicate);
        // printResultArray(isAll);
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

reverse(array)
{
    arr = [];
    index = 0;

    for (i = array.size; i != 0; i--)
    {
        arr[index] = array[i];
        index++;
    }
    return arr;
}

repeat(array, count)
{
    arr = [];
    index = 0;

    for (r = 0; r < count; r++)
    {
        for (i = 0; i < array.size; i++)
        {
            arr[index] = array[i];
            index++;
        }
    }
    return arr;
}

range(array, min, max)
{
    arr = [];
    index = 0;
    if (!isDefined(max))
        max = array.size;

    for (i = min; i < max; i++)
    {
        arr[index] = array[i];
        index++;
    }
    return arr;
}

select(array, func)
{
    arr = [];

    for (i = 0; i < array.size; i++)
        array[i] = [[func]](array[i]);
    return arr;
}

sum(array)
{
    ret = 0;
    for (i = 0; i < array.size; i++)
        ret += array[i];
    return ret;
}

count(array, predicate)
{
    ret = 0;
    for (i = 0; i < array.size; i++)
    {
        if ([[predicate]](array[i]))
            ret++;
    }
    return ret;
}

average(array)
{
    sum = array[0];
    count = 1;
    for (i = 0; i < array.size; i++)
    {
        sum += array[i];
        count++;
    }
    return int(sum / count); // todo float
}

getType(var)
{

}

orderBy(array)
{

}

sort(array)
{

}

sortType(array, type)
{

}

cast(array, type)
{

}

first(array, predicate)
{
    ret = undefined;
    for (i = 0; i < array.size; i++)
    {
        if ([[predicate]](array[i]))
            return array[i];
    }
    return ret;
}

last(array, predicate)
{
    ret = undefined;
    for (i = 0; i < array.size; i++)
    {
        if ([[predicate]](array[i]))
            ret = array[i];
    }
    return ret;
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

any(array, predicate)
{
    for (i = 0; i < array.size; i++)
    {
        if ([[predicate]](array[i]))
            return true;
    }
    return false;
}
