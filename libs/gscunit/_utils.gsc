logArrayTypes(arr)
{
	if (isDefined(arr) && isDefined(arr.size))
	{
		for (i = 0; i < arr.size; i++)
		{
			if (isDefined(arr[i]))
				comPrintf(GetType(arr[i]) + " " + arr[i] + "\n");
		}
	}
}

logArrayKeys(arr)
{
	if (isDefined(arr))
	{
		keys = getArrayKeys(arr);
		if (isDefined(keys) && isDefined(keys.size))
		{
			for (i = 0; i < keys.size; i++)
			{
				if (isDefined(arr[keys[i]]))
					comPrintf(keys[i] + ": " + arr[keys[i]] + "\n");
			}
		}
	}
}

logArray(arr)
{
	if (isDefined(arr) && isDefined(arr.size))
	{
		for (i = 0; i < arr.size; i++)
		{
			if (isDefined(arr[i]))
				comPrintf(arr[i] + "\n");
		}
	}
}

logVariable(var)
{
	if (isDefined(var))
		comPrintf(var + "\n");
}

logVariableType(var)
{
	if (isDefined(var))
		comPrintf(GetType(var) + " " + var + "\n");
}

spawnBots(number)
{
	for (i = 0; i < number; i++)
	{
		bot = addTestClient();
		wait 0.05;
		bot notify("menuresponse", game["menu_team"], "autoassign");
	}
}
