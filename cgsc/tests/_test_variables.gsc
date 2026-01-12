#include sr\libs\gscunit\_main;
#include sr\libs\cgsc\__test__\_suite;

main()
{
	suite("CGSC Variables");

	it(::test_Int, "Int");
	it(::test_Array, "Array");
	it(::test_Array2D, "Array2D");
	it(::test_Array3D, "Array3D");
	it(::test_Struct, "Struct");

	it(::test_Predicate, "Predicate");
	it(::test_ScriptUsage, "ScriptUsage");
}

test_Int()
{
	for (i = 0; i < 10000; i++)
		a = IfUndef(i, 0);
}

test_Array()
{
	a = [];
	for (i = 0; i < 10000; i++)
		a[i] = IfUndef(i, 0);
}

test_Array2D()
{
	a = [];
	for (i = 0; i < 10000; i++)
	{
		b = [];
		for (j = 0; j < 3; j++)
			b[j] = j + 1;
		a[i] = IfUndef(b, []);
	}
	count = 0;
	sum = 0;
	for (i = 0; i < a.size; i++)
	{
		count += a[i].size;
		for (j = 0; j < a[i].size; j++)
			sum += a[i][j];
	}

	comPrintLn("count: %d", count);
	comPrintLn("sum: %d", sum);
	EXPECT_EQ(count, 30000);
	EXPECT_EQ(sum, 60000);
}

test_Array3D()
{
	a = [];
	for (i = 0; i < 5000; i++)
	{
		b = [];
		for (j = 0; j < 2; j++)
		{
			c = [];
			for (k = 0; k < 2; k++)
				c[k] = k + 1;

			b[j] = c;
		}
		a[i] = IfUndef(b, []);
	}
	count = 0;
	sum = 0;
	for (i = 0; i < a.size; i++)
	{
		for (j = 0; j < a[i].size; j++)
		{
			count += a[i][j].size;
			for (k = 0; k < a[i][j].size; k++)
				sum += a[i][j][k];
		}
	}

	comPrintLn("count: %d", count);
	comPrintLn("sum: %d", sum);
	EXPECT_EQ(count, 20000);
	EXPECT_EQ(sum, 30000);
}

test_Struct()
{
	a = [];
	for (i = 0; i < 10000; i++)
	{
		s = spawnStruct();
		s.value = 10;

		a[i] = IfUndef(s, 0);
	}
	sum = 0;
	for (i = 0; i < a.size; i++)
		sum += a[i].value;

	comPrintLn("sum: %d", sum);
	EXPECT_EQ(sum, 100000);
}

test_Predicate()
{
	a = [];
	a[0] = 0;
	a[1] = 1;
	a[2] = 2;

	b = [];
	for (i = 0; i < 10000; i++)
		b[i] = Where(a, ::predicate);

	count = 0;
	for (i = 0; i < b.size; i++)
		count += b[i].size;

	comPrintLn("count: %d", count);
	EXPECT_EQ(count, 20000);
}

test_ScriptUsage()
{
	usage = debug_scriptusage();
	comPrintLn("script usage: %d", usage);
	EXPECT_LE(usage, 1000);
}

predicate(item, index)
{
	return item > 0;
}
