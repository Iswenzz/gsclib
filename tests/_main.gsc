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

	comPrintf("\n|-------------------[GSCLIB Tests]-------------------|\n");
	// lib\gsclib\_tests_linq::test(false);
	// lib\gsclib\_tests_utility::test(false);
	// lib\gsclib\_tests_data::test(false);
	// lib\gsclib\_tests_net::test(false);
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

// Test predicate
testPredicate(item)
{
	return isDefined(item) && item != 5;
}

// Test predicate vector
testPredicateVector(item)
{
	return isDefined(item) && item != (0, 0, 0);
}

// Test predicate string
testPredicateString(item)
{
	return isDefined(item) && item != "Iswenzz";
}

// test predicate array
testPredicateArray(item)
{
	return isDefined(item) && isDefined(item.size) && item.size != 10;
}

// test predicate struct.name
testPredicateStructString(item)
{
	return isDefined(item) && isDefined(item.string) && item.string != "M1014";
}

// test predicate struct.int
testPredicateStructInt(item)
{
	return isDefined(item) && isDefined(item.int) && item.int != 8;
}

// Test delegate struct.string
testDelegateStructString(item)
{
	if (isDefined(item) && isDefined(item.string))
		return item.string;
	else
		return "";
}

// Test delegate struct.int
testDelegateStructInt(item)
{
	if (isDefined(item) && isDefined(item.int))
		return item.int;
	else
		return 0;
}

// Test predicate player ent
testPredicateEnt(player)
{
	return isDefined(player) && isDefined(player.name) && player.name != "Iswenzz";
}
