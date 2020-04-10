#include lib\gsclib\_main;

// Tests for gsclib/data
test(loop)
{
	comPrintF("\n[======{Data}======]\n");

	while (true)
	{
		it_RegexMatch();
		it_RegexReplace();
		it_RegexSplit();
		
		it_SQL_Version();
		it_SQL_Connect();
		it_SQL_SelectDB();
		it_SQL_ListDB();
		it_SQL_Query();
		it_SQL_NumRows();
		it_SQL_NumFields();
		it_SQL_FetchRow();
		it_SQL_FetchRows();
		it_SQL_Close();

		if (!loop)
			break;
		wait 0.05;
	}
}

it_SQL_Query()
{
	comPrintF("\n<-------[SQL_Query]------->\n");
	SQL_Query("SELECT * FROM players");
}

it_SQL_FetchRow()
{
	comPrintF("\n<-------[FetchRow]------->\n");
	SQL_Query("SELECT * FROM players");
	printArray(SQL_FetchRow());
}

it_SQL_FetchRows()
{
	comPrintF("\n<-------[FetchRows]------->\n");
	SQL_Query("SELECT * FROM players");

	rows = SQL_FetchRows();
	if (isDefined(rows) && isDefined(rows.size))
	{
		for (i = 0; i < rows.size; i++)
			printArray(rows[i]);
	}
}

it_SQL_NumFields()
{
	comPrintF("\n<-------[NumFields]------->\n");
	printVariable(SQL_NumFields());
}

it_SQL_NumRows()
{
	comPrintF("\n<-------[NumRows]------->\n");
	printVariable(SQL_NumRows());
}

it_SQL_SelectDB()
{
	comPrintF("\n<-------[SQL_SelectDB]------->\n");
	SQL_SelectDB("testdb");
}

it_SQL_ListDB()
{
	comPrintF("\n<-------[SQL_ListDB]------->\n");
	printArray(SQL_ListDB());
}

it_SQL_Version()
{
	comPrintF("\n<-------[SQL_Version]------->\n");
	SQL_Version();
}

it_SQL_Connect()
{
	comPrintF("\n<-------[SQL_Connect]------->\n");
	SQL_Connect("127.0.0.1", 3306, "root", "rootpassword");
}

it_SQL_Close()
{
	comPrintF("\n<-------[SQL_Close]------->\n");
	SQL_Close();
}

it_RegexMatch()
{
	comPrintF("\n<-------[RegexMatch]------->\n");
	printArray(RegexMatch("zzzz123affff12345ffffb", "\\d+"));
}

it_RegexSplit()
{
	comPrintF("\n<-------[RegexSplit]------->\n");
	printArray(RegexSplit("zzzz123affff12345ffffb", "\\d+"));
}

it_RegexReplace()
{
	comPrintF("\n<-------[RegexReplace]------->\n");
	printVariable(RegexReplace("zzzz123affff12345ffffb", "", "\\d+"));
}
