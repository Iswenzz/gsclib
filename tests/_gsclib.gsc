// Main tests
runTests()
{
    wait 10;

    comPrintf("\n|-------------------[gsclib tests]-------------------|\n");
    lib\_tests_linq::test();
    lib\_tests_collections::test();
    comPrintf("\n|----------------------------------------------------|\n");
}

// Main tests on player ent
runPlayerTests()
{
    wait 5;
}

// Print all items in the array with their type.
printArrayWithType(arr)
{
    if (isDefined(arr) && isDefined(arr.size))
    {
        for (i = 0; i < arr.size; i++)
        {
            if (isDefined(arr[i]))
            {
                msg = "" + arr[i] + " " + GetType(arr[i]);
                iprintlnbold(msg);
                comPrintf(msg + "\n");
            }
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
            if (isDefined(arr[i]))
            {
                msg = "" + arr[i];
                iprintlnbold(msg);
                comPrintf(msg + "\n");
            }
        }
    }
}

// Print variable
printVariable(var)
{
    if (isDefined(var))
    {
         msg = "" + var;
        iprintlnbold(msg);
        comPrintf(msg + "\n");
    }
}

// Print variable with its type
printVariableWithType(var)
{
    if (isDefined(var))
    {
        msg = "" + var + " " + GetType(var);
        iprintlnbold(msg);
        comPrintf(msg + "\n");
    }
}

// Test predicate
testPredicate(item)
{
    return item != 5;
}

// Test predicate vector
testPredicateVector(item)
{
    return item != (0, 0, 0);
}

// Test predicate string
testPredicateString(item)
{
    return item != "Iswenzz";
}

// Test delegate struct member "name"
testDelegateName(item)
{
    return item.name;
}

// Test delegate struct member "bullet"
testDelegateBullet(item)
{
    return item.bullet;
}
