#include sr\tests\_main;

// Tests for gsclib/data
test()
{
	suit("GSCLIB - Data");

	level.MYSQL_TYPE_DECIMAL      = 0;
	level.MYSQL_TYPE_TINY         = 1;
	level.MYSQL_TYPE_SHORT        = 2;
	level.MYSQL_TYPE_LONG         = 3;
	level.MYSQL_TYPE_FLOAT        = 4;
	level.MYSQL_TYPE_DOUBLE       = 5;
	level.MYSQL_TYPE_NULL         = 6;
	level.MYSQL_TYPE_TIMESTAMP    = 7;
	level.MYSQL_TYPE_LONGLONG     = 8;
	level.MYSQL_TYPE_INT24        = 9;
	level.MYSQL_TYPE_DATE         = 10;
	level.MYSQL_TYPE_TIME         = 11;
	level.MYSQL_TYPE_DATETIME     = 12;
	level.MYSQL_TYPE_YEAR         = 13;
	level.MYSQL_TYPE_NEWDATE      = 14;
	level.MYSQL_TYPE_VARCHAR      = 15;
	level.MYSQL_TYPE_BIT          = 16;
	level.MYSQL_TYPE_TIMESTAMP2   = 17;
	level.MYSQL_TYPE_DATETIME2    = 18;
	level.MYSQL_TYPE_TIME2        = 19;
	level.MYSQL_TYPE_JSON         = 245;
	level.MYSQL_TYPE_NEWDECIMAL   = 246;
	level.MYSQL_TYPE_ENUM         = 247;
	level.MYSQL_TYPE_SET          = 248;
	level.MYSQL_TYPE_TINY_BLOB    = 249;
	level.MYSQL_TYPE_MEDIUM_BLOB  = 250;
	level.MYSQL_TYPE_LONG_BLOB    = 251;
	level.MYSQL_TYPE_BLOB         = 252;
	level.MYSQL_TYPE_VAR_STRING   = 253;
	level.MYSQL_TYPE_STRING       = 254;
	level.MYSQL_TYPE_GEOMETRY     = 255;

	run(::it_RegexMatch, "RegexMatch");
	run(::it_RegexReplace, "RegexReplace");
	run(::it_RegexSplit, "RegexSplit");
	
	run(::it_SQL_Version, "SQL_Version");
	run(::it_SQL_Connect, "SQL_Connect");

	run(::it_SQL_SelectDB, "SQL_SelectDB");
	run(::it_SQL_ListDB, "SQL_ListDB");
	run(::it_SQL_ListTables, "SQL_ListTables");

	run(::it_SQL_Query, "SQL_Query");
	run(::it_SQL_AffectedRows, "SQL_AffectedRows");
	run(::it_SQL_NumRows, "SQL_NumRows");
	run(::it_SQL_NumFields, "SQL_NumFields");
	run(::it_SQL_FetchFields, "SQL_FetchFields");
	run(::it_SQL_FetchRowDict, "SQL_FetchRowDict");
	run(::it_SQL_FetchRow, "SQL_FetchRow");
	run(::it_SQL_FetchRowsDict, "SQL_FetchRowsDict");
	run(::it_SQL_FetchRows, "SQL_FetchRows");

	run(::it_SQL_PrepareBindParam, "SQL_PrepareBindParam");
	run(::it_SQL_Execute, "SQL_Execute");
	run(::it_SQL_FetchRowDict, "SQL_FetchRowDict");

	run(::it_SQL_PrepareBindResult, "SQL_PrepareBindResult");
	run(::it_SQL_Execute, "SQL_Execute");
	run(::it_SQL_AffectedRows, "SQL_AffectedRows");
	run(::it_SQL_NumRows, "SQL_NumRows");
	run(::it_SQL_NumFields, "SQL_NumFields");
	run(::it_SQL_FetchFields, "SQL_FetchFields");
	run(::it_SQL_FetchRowDict, "SQL_FetchRowDict");

	run(::it_SQL_HexString, "SQL_HexString");
	run(::it_SQL_EscapeString, "SQL_EscapeString");
	run(::it_SQL_Close, "SQL_Close");
}

it_SQL_PrepareBindResult()
{
	printVariable(SQL_Prepare("SELECT name, guid, xp, rank, prestige FROM speedrun_ranks WHERE name = ?"));
	SQL_BindParam("Iswenzz", level.MYSQL_TYPE_VAR_STRING);
	SQL_BindResult(level.MYSQL_TYPE_VAR_STRING, 60);
	SQL_BindResult(level.MYSQL_TYPE_VAR_STRING, 60);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
}

it_SQL_PrepareBindParam()
{
	printVariable(SQL_Prepare("INSERT INTO speedrun_ranks (name, guid, xp, rank, prestige) VALUES (?, ?, ?, ?, ?)"));
	SQL_BindParam("Iswenzz", level.MYSQL_TYPE_VAR_STRING);
	SQL_BindParam("313354b4", level.MYSQL_TYPE_VAR_STRING);
	SQL_BindParam("1296000", level.MYSQL_TYPE_LONG);
	SQL_BindParam("80", level.MYSQL_TYPE_LONG);
	SQL_BindParam("10", level.MYSQL_TYPE_LONG);
	SQL_Execute();
}

it_SQL_Execute()
{
	printVariable(SQL_Execute());
}

it_SQL_HexString()
{
	printVariable(SQL_HexString("Iswenzz"));
}

it_SQL_EscapeString()
{
	printVariable(SQL_EscapeString("\\"));
}

it_SQL_AffectedRows()
{
	printVariable(SQL_AffectedRows());
}

it_SQL_Query()
{
	printVariable(SQL_Query("SELECT * FROM speedrun_ranks"));
}

it_SQL_FetchFields()
{
	printArray(SQL_FetchFields());
}

it_SQL_FetchRow()
{
	printArray(SQL_FetchRow());
}

it_SQL_FetchRows()
{
	rows = SQL_FetchRows();
	if (isDefined(rows) && isDefined(rows.size))
	{
		for (i = 0; i < rows.size; i++)
			printArray(rows[i]);
	}
}

it_SQL_FetchRowDict()
{
	printArrayKeys(SQL_FetchRowDict());
}

it_SQL_FetchRowsDict()
{
	rows = SQL_FetchRowsDict();
	if (isDefined(rows) && isDefined(rows.size))
	{
		for (i = 0; i < rows.size; i++)
			printArrayKeys(rows[i]);
	}
}

it_SQL_NumFields()
{
	printVariable(SQL_NumFields());
}

it_SQL_NumRows()
{
	printVariable(SQL_NumRows());
}

it_SQL_SelectDB()
{
	printVariable(SQL_SelectDB("sr"));
}

it_SQL_ListDB()
{
	printArray(SQL_ListDB());
}

it_SQL_ListTables()
{
	printArray(SQL_ListTables());
}

it_SQL_Version()
{
	printVariable(SQL_Version());
}

it_SQL_Connect()
{
	printVariable(SQL_Connect("127.0.0.1", 3306, "root", "rootpassword"));
}

it_SQL_Close()
{
	printVariable(SQL_Close());
}

it_RegexMatch()
{
	printArray(RegexMatch("zzzz123affff12345ffffb", "\\d+"));
}

it_RegexSplit()
{
	printArray(RegexSplit("zzzz123affff12345ffffb", "\\d+"));
}

it_RegexReplace()
{
	printVariable(RegexReplace("zzzz123affff12345ffffb", "", "\\d+"));
}
