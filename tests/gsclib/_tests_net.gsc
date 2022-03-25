#include sr\tests\_main;

// Tests for gsclib/net
test()
{
	suit("GSCLIB - Net");

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

	// net/curl
	run(::it_CURL_Version, "CURL_Version");
	run(::it_CURL_HeaderCleanup, "CURL_HeaderCleanup");
	run(::it_CURL_OptCleanup, "CURL_OptCleanup");

	// net/ftp
	run(::it_SFTP_Connect, "SFTP_Connect");
	run(::it_FTP_PostFile, "FTP_PostFile");
	run(::it_FTP_Shell, "FTP_Shell");
	run(::it_FTP_GetFile, "FTP_GetFile");
	run(::it_FTP_Close, "FTP_Close");

	// net/https
	run(::it_HTTPS_GetFile, "HTTPS_GetFile");
	run(::it_HTTPS_GetString, "HTTPS_GetString");
	run(::it_HTTPS_PostFile, "HTTPS_PostFile");
	run(::it_HTTPS_PostString, "HTTPS_PostString");

	// net/mysql
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

it_CURL_Version()
{
	CURL_Version();
}

it_CURL_HeaderCleanup()
{
	CURL_HeaderCleanup();
}

it_CURL_OptCleanup()
{
	CURL_OptCleanup();
}

it_HTTPS_GetFile()
{
	CURL_AddOpt(41, 1);
	printVariable(HTTPS_GetFile("test/version.txt", "https://iswenzz.com:1337/speedrun_app/version.txt"));
}

it_HTTPS_GetString()
{
	printVariable(HTTPS_GetString("http://httpbin.org/get"));
}

it_HTTPS_PostFile()
{
	printVariable(HTTPS_PostFile("test/version.txt", "http://httpbin.org/post"));
}

it_HTTPS_PostString()
{
	CURL_SetHeader("Accept: application/json,Content-Type: application/json");
	printVariable(HTTPS_PostString("{\"login\":\"login\",\"password\":\"password\"}", "http://httpbin.org/post"));
}

it_SFTP_Connect()
{
	// Or FTP_Connect.
	printVariable(SFTP_Connect("localhost", "root", "rootpassword", 22));
}

it_FTP_PostFile()
{
	printVariable(FTP_PostFile("libcurl.dll", "libcurl.dll"));
}

it_FTP_Shell()
{
	// CURL_SetHeader("RNFR libcurl.dll,RNTO test.dll"); // FTP cmd
	CURL_SetHeader("rename libcurl.dll test.dll"); // SFTP cmd
	printVariable(FTP_Shell());
}

it_FTP_GetFile()
{
	printVariable(FTP_GetFile("test.dll", "test.dll"));
}

it_FTP_Close()
{
	printVariable(FTP_Close());
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
