#include libs\gscunit\_utils;

gscunit()
{
	level.gscunit = spawnStruct();
	level.gscunit.debug = false;
	level.gscunit.fail = false;
	level.gscunit.count_pass = 0;
	level.gscunit.count_fail = 0;
}

it(callback, name, beforeCallback, afterCallback)
{
	// Before
	comPrintF(name + " ");
	if (isDefined(beforeCallback) && ![[beforeCallback]]())
	{
		comPrintF(" (ERROR beforeCallback)\n");
		return;
	}
	comPrintF("\n");

	// Test
	clock = startClock();
    [[callback]]();
	time = stopClock(clock);

	// Result
	result = Ternary(level.gscunit.fail, "FAIL", "PASS");
	comPrintF(name + " " + result + " (" + time + "ms) ");

	// After
	if (isDefined(afterCallback) && ![[afterCallback]]())
		comPrintF(" (ERROR afterCallback)\n");
	comPrintF("\n");

	// Summarize
	if (result == "PASS")
		level.gscunit.count_pass++;
	else
		level.gscunit.count_fail++;
	level.gscunit.fail = false;
}

suite(name)
{
    comPrintf("\n<|>-------------------[" + name + "]-------------------<|>\n");
}

startClock()
{
	return getTime();
}

stopClock(clock)
{
	return getTime() - clock;
}

summarize()
{
	comPrintf("\nPassed: " + level.gscunit.count_pass + " Failed: " + level.gscunit.count_fail + "\n\n");

	level.gscunit.fail = false;
	level.gscunit.count_pass = 0;
	level.gscunit.count_fail = 0;
}

FAIL()
{
	level.gscunit.fail = true;
	return false;
}

EXPECT_EQ(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] == b[0] && a[1] == b[1] && a[2] == b[2])
				return true;
			break;

		default:
			if (a == b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_NE(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] != b[0] && a[1] != b[1] && a[2] != b[2])
				return true;
			break;

		default:
			if (a != b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_CONTAIN(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] == b || a[1] == b || a[2] == b)
				return true;
			break;

		case "ARRAY":
			for (i = 0; i < a.size; i++)
			{
				if (a[i] == b)
					return true;
			}
			break;

		case "STRING":
		case "ISTRING":
			if (isSubStr(a, b))
				return true;
			break;

		default:
			if (a == b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_NOT_CONTAIN(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] != b || a[1] != b || a[2] != b)
				return true;
			break;

		case "ARRAY":
			found = false;
			for (i = 0; i < a.size; i++)
			{
				if (a[i] == b)
				{
					found = true;
					break;
				}
			}
			if (!found)
				return true;
			break;

		case "STRING":
		case "ISTRING":
			if (!isSubStr(a, b))
				return true;
			break;

		default:
			if (a != b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_TRUE(a)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] && a[1] && a[2])
				return true;
			break;

		default:
			if (a)
				return true;
			break;
	}

	error_expect(true, a);
	return FAIL();
}

EXPECT_FALSE(a)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (!a[0] && !a[1] && !a[2])
				return true;
			break;

		default:
			if (!a)
				return true;
			break;
	}

	error_expect(false, a);
	return FAIL();
}

EXPECT_UNDEFINED(a)
{
	gscunit_debug(a);
	if (!isDefined(a)) return true;

	error_expect(undefined, a);
	return FAIL();
}

EXPECT_LT(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] < b[0] && a[1] < b[1] && a[2] < b[2])
				return true;
			break;

		default:
			if (a < b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_LE(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] <= b[0] && a[1] <= b[1] && a[2] <= b[2])
				return true;
			break;

		default:
			if (a <= b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_GT(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] > b[0] && a[1] > b[1] && a[2] > b[2])
				return true;
			break;

		default:
			if (a > b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_GE(a, b)
{
	gscunit_debug(a);
	switch (GetType(a))
	{
		case "UNDEFINED":
			break;

		case "VECTOR":
			if (a[0] >= b[0] && a[1] >= b[1] && a[2] >= b[2])
				return true;
			break;

		default:
			if (a >= b)
				return true;
			break;
	}

	error_expect(a, b);
	return FAIL();
}

EXPECT_TYPE(a, b)
{
	gscunit_debug(a);
	if (GetType(a) != GetType(b)) return true;

	error_expect(GetType(a), GetType(a));
	return FAIL();
}

printable(a)
{
	switch (GetType(a))
	{
		case "ARRAY":
			string = "[";
			for (i = 0; i < a.size; i++)
				string += printable(a[i]) + ", ";
			return getSubStr(string, 0, string.size - 2) + "]";

		case "STRING":
		case "ISTRING":
		case "VECTOR":
		case "FLOAT":
		case "INTEGER":
			return a;
	}
	return "";
}

error_expect(a, b)
{
	received = printable(a);
	expected = printable(b);

	comPrintF("\n\tReceived: " + received + "\n\tExpected: " + expected + "\n\n");
}

gscunit_debug(a)
{
	if (!level.gscunit.debug) return;

	switch (GetType(a))
	{
		case "ARRAY":
			logArrayTypes(a);
			break;

		case "UNDEFINED":
		case "STRING":
		case "ISTRING":
		case "VECTOR":
		case "FLOAT":
		case "INTEGER":
			logVariableType(a);
			break;
	}
}
