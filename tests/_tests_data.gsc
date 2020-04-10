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
		it_SQL_ListTables();
		it_SQL_Query();
		it_SQL_AffectedRows();
		it_SQL_NumRows();
		it_SQL_NumFields();
		it_SQL_FetchFields();
		it_SQL_FetchRow();
		it_SQL_FetchRows();
		it_SQL_HexString();
		it_SQL_EscapeString();
		it_SQL_Close();

		if (!loop)
			break;
		wait 0.05;
	}
}

it_SQL_HexString()
{
	comPrintF("\n<-------[SQL_HexString]------->\n");
	printVariable(SQL_HexString("Iswenzz"));
}

it_SQL_EscapeString()
{
	comPrintF("\n<-------[SQL_EscapeString]------->\n");
	printVariable(SQL_EscapeString("\\"));
}

it_SQL_AffectedRows()
{
	comPrintF("\n<-------[SQL_AffectedRows]------->\n");
	SQL_Query("SELECT * FROM players");
	printVariable(SQL_AffectedRows());
}

it_SQL_Query()
{
	comPrintF("\n<-------[SQL_Query]------->\n");
	printVariable(SQL_Query("SELECT * FROM players"));
}

it_SQL_FetchFields()
{
	comPrintF("\n<-------[SQL_FetchFields]------->\n");
	SQL_Query("SELECT * FROM players");
	printArray(SQL_FetchFields());
}

it_SQL_FetchRow()
{
	comPrintF("\n<-------[SQL_FetchRow]------->\n");
	SQL_Query("SELECT * FROM players");
	printArray(SQL_FetchRow());
}

it_SQL_FetchRows()
{
	comPrintF("\n<-------[SQL_FetchRows]------->\n");
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
	comPrintF("\n<-------[SQL_NumFields]------->\n");
	printVariable(SQL_NumFields());
}

it_SQL_NumRows()
{
	comPrintF("\n<-------[SQL_NumRows]------->\n");
	printVariable(SQL_NumRows());
}

it_SQL_SelectDB()
{
	comPrintF("\n<-------[SQL_SelectDB]------->\n");
	printVariable(SQL_SelectDB("testdb"));
}

it_SQL_ListDB()
{
	comPrintF("\n<-------[SQL_ListDB]------->\n");
	printArray(SQL_ListDB());
}

it_SQL_ListTables()
{
	comPrintF("\n<-------[SQL_ListTables]------->\n");
	printArray(SQL_ListTables());
}

it_SQL_Version()
{
	comPrintF("\n<-------[SQL_Version]------->\n");
	printVariable(SQL_Version());
}

it_SQL_Connect()
{
	comPrintF("\n<-------[SQL_Connect]------->\n");
	printVariable(SQL_Connect("127.0.0.1", 3306, "root", "rootpassword"));
}

it_SQL_Close()
{
	comPrintF("\n<-------[SQL_Close]------->\n");
	printVariable(SQL_Close());
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
