// Run all tests suits.
run()
{
    wait 5;
    spawnBots();

    sr\tests\gsclib\_main::test();
}

spawnBots()
{
	for (i = 0; i < 5; i++)
	{
		bot = addTestClient();
		wait 0.05;
		bot notify("menuresponse", game["menu_team"], "autoassign");
	}
}

// Run a specific test case and print a log message with the test name.
run(func, name)
{
    comPrintF("\n<-------[" + name + "]------->\n");
    [[func]]();
}

// Print a log message with the suit name.
suit(name)
{
    comPrintf("\n|-------------------[" + name + "]-------------------|\n");
}

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

printArrayKeys(arr)
{
	if (isDefined(arr))
	{
		keys = getArrayKeys(arr);
		if (isDefined(keys) && isDefined(keys.size))
		{
			for (i = 0; i < keys.size; i++)
			{
				if (isDefined(arr[keys[i]]))
				{
					msg = keys[i] + ": " + arr[keys[i]];
					iprintlnbold(msg);
					comPrintf(msg + "\n");
				}
			}
		}
	}
}

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

printVariable(var)
{
	if (isDefined(var))
	{
		msg = "" + var;
		iprintlnbold(msg);
		comPrintf(msg + "\n");
	}
}

printVariableWithType(var)
{
	if (isDefined(var))
	{
		msg = "" + var + " " + GetType(var);
		iprintlnbold(msg);
		comPrintf(msg + "\n");
	}
}
