// Main tests
runTests()
{
    wait 10;
    // spawn bots for testing ents
    for (i = 0; i < 5; i++)
    {
        bot = addTestClient();
        wait 0.05;
        bot notify("menuresponse", game["menu_team"], "autoassign");
    }

    comPrintf("\n|-------------------[gsclib tests]-------------------|\n");
    lib\gsclib\_tests_linq::test();
    lib\gsclib\_tests_collections::test();
    comPrintf("\n|----------------------------------------------------|\n");
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

// Test predicate player ent
testPredicateEnt(player)
{
    return player.name != "Iswenzz";
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

// test predicate array
testPredicateArray(item)
{
    return item.size != 10;
}

// test predicate struct.name
testPredicateName(item)
{
    return item.name != "M1014";
}

// test predicate struct.bullet
testPredicateBullet(item)
{
    return item.bullet != 8;
}

// Test delegate struct.name
testDelegateName(item)
{
    return item.name;
}

// Test delegate struct.bullet
testDelegateBullet(item)
{
    return item.bullet;
}
