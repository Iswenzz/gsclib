#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Network");

	setup();

	// Network/FTP
	it(::test_FTP_PostGetFile, "FTP_PostGetFile", ::beforeFTP, ::afterFTP);
	it(::test_SFTP_Shell, "SFTP_Shell", ::beforeSFTP, ::afterSFTP);
	it(::test_FTP_PostGetFile, "FTP_PostGetFile", ::beforeFTP, ::afterFTP);
	it(::test_FTP_Shell, "FTP_Shell", ::beforeFTP, ::afterFTP);
	it(::test_FTP_HeaderCleanup, "FTP_HeaderCleanup", ::beforeFTP, ::afterFTP);
	it(::test_FTP_OptCleanup, "FTP_OptCleanup", ::beforeFTP, ::afterFTP);
	it(::test_FTP_AddOpt, "FTP_AddOpt", ::beforeFTP, ::afterFTP);

	// Network/HTTP
	it(::test_HTTP_Get, "HTTP_Get");
	it(::test_HTTP_GetFile, "HTTP_GetFile");
	it(::test_HTTP_Post, "HTTP_Post");
	it(::test_HTTP_PostFile, "HTTP_PostFile");
	it(::test_HTTP_HeaderCleanup, "HTTP_HeaderCleanup");
	it(::test_HTTP_OptCleanup, "HTTP_OptCleanup");
	it(::test_HTTP_AddOpt, "HTTP_AddOpt");

	// Network/MySQL
	it(::test_SQL_Version, "SQL_Version", ::beforeMySQL, ::afterMySQL);
	it(::test_SQL_HexString, "SQL_HexString", ::beforeMySQL, ::afterMySQL);
	it(::test_SQL_EscapeString, "SQL_EscapeString", ::beforeMySQL, ::afterMySQL);
	it(::test_SQL_SelectDB, "SQL_SelectDB", ::beforeMySQL, ::afterMySQL);
	it(::test_SQL_ListDB, "SQL_ListDB", ::beforeMySQL, ::afterMySQL);
	it(::test_SQL_ListTables, "SQL_ListTables", ::beforeMySQL, ::afterMySQL);
	it(::test_SQL_PrepareStatement, "SQL_PrepareStatement", ::beforeMySQL, ::afterMySQL);
	it(::test_SQL_Query, "SQL_Query", ::beforeMySQL, ::afterMySQL);
}

setup()
{
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
	level.MYSQL_TYPE_STRING       = 253;
	level.MYSQL_TYPE_TEXT         = 254;
	level.MYSQL_TYPE_GEOMETRY     = 255;
}

beforeSFTP()
{
	if (!hasSFTP())
		return false;
	return SFTP_Connect("127.0.0.1", "root", "rootpassword", 22);
}

afterSFTP()
{
	if (!hasSFTP())
		return false;
	return FTP_Close();
}

beforeFTP()
{
	if (!hasFTP())
		return false;
	return FTP_Connect("127.0.0.1", "root", "rootpassword", 21);
}

afterFTP()
{
	if (!hasFTP())
		return false;
	return FTP_Close();
}

beforeMySQL()
{
	if (!hasMySQL())
		return false;
	if (!SQL_Connect("127.0.0.1", 3306, "root", "rootpassword"))
		return false;
	return SQL_SelectDB("speedrun");
}

afterMySQL()
{
	if (!hasMySQL())
		return false;
	return SQL_Close();
}

test_HTTP_Get()
{
	url = "http://httpbin.org/get";

	request = HTTP_Init();
	HTTP_Get(request, url);
	EXPECT_EQ(AsyncWait(request), 2);

	EXPECT_CONTAIN(HTTP_Response(request), "httpbin.org");
	EXPECT_TRUE(HTTP_Free(request));
}

test_HTTP_GetFile()
{
	url = "https://iswenzz.com/";

	request = HTTP_Init();
	EXPECT_TRUE(HTTP_GetFile(request, "temp/iswenzz.html", url));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(HTTP_Free(request));
}

test_HTTP_Post()
{
	json = "{\"login\":\"login\",\"password\":\"password\"}";
	url = "http://httpbin.org/post";

	request = HTTP_Init();
	HTTP_AddHeader(request, "Accept: application/json,Content-Type: application/json");
	HTTP_Post(request, json, url);
	EXPECT_EQ(AsyncWait(request), 2);

	EXPECT_CONTAIN(HTTP_Response(request), "password");
	EXPECT_TRUE(HTTP_Free(request));
}

test_HTTP_PostFile()
{
	url = "http://httpbin.org/post";

	request = HTTP_Init();
	HTTP_PostFile(request, "temp/iswenzz.html", url);
	EXPECT_EQ(AsyncWait(request), 2);

	EXPECT_CONTAIN(HTTP_Response(request), "Iswenzz");
	EXPECT_TRUE(HTTP_Free(request));
	FILE_Delete("temp/iswenzz.html");
}

test_HTTP_HeaderCleanup()
{
	request = HTTP_Init();
	EXPECT_UNDEFINED(HTTP_HeaderCleanup(request));
	EXPECT_TRUE(HTTP_Free(request));
}

test_HTTP_OptCleanup()
{
	request = HTTP_Init();
	EXPECT_UNDEFINED(HTTP_OptCleanup(request));
	EXPECT_TRUE(HTTP_Free(request));
}

test_HTTP_AddOpt()
{
	request = HTTP_Init();
	EXPECT_UNDEFINED(HTTP_AddOpt(request, 41, 1));
	EXPECT_TRUE(HTTP_Free(request));
}

test_SFTP_Shell()
{
	request = FTP_Init();
	FTP_AddHeader(request, "rename ftp.txt new.txt");
	EXPECT_TRUE(FTP_Shell(request));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(FTP_Free(request));

	request = FTP_Init();
	FTP_AddHeader(request, "rm new.txt");
	EXPECT_TRUE(FTP_Shell(request));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(FTP_Free(request));
}

test_FTP_Shell()
{
	request = FTP_Init();
	FTP_AddHeader(request, "RNFR ftp.txt");
	FTP_AddHeader(request, "RNTO new.txt");
	EXPECT_TRUE(FTP_Shell(request));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(FTP_Free(request));

	request = FTP_Init();
	FTP_AddHeader(request, "DELE new.txt");
	EXPECT_TRUE(FTP_Shell(request));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(FTP_Free(request));
}

test_FTP_PostGetFile()
{
	FILE_Create("temp/test.txt");

	request = FTP_Init();
	EXPECT_TRUE(FTP_PostFile(request, "temp/test.txt", "ftp.txt"));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(FTP_Free(request));

	FILE_Delete("temp/test.txt");

	request = FTP_Init();
	EXPECT_TRUE(FTP_GetFile(request, "temp/ftp.txt", "ftp.txt"));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(FTP_Free(request));

	FILE_Delete("temp/ftp.txt");
}

test_FTP_HeaderCleanup()
{
	request = FTP_Init();
	EXPECT_UNDEFINED(FTP_HeaderCleanup(request));
	EXPECT_TRUE(FTP_Free(request));
}

test_FTP_OptCleanup()
{
	request = FTP_Init();
	EXPECT_UNDEFINED(FTP_OptCleanup(request));
	EXPECT_TRUE(FTP_Free(request));
}

test_FTP_AddOpt()
{
	request = FTP_Init();
	EXPECT_UNDEFINED(FTP_AddOpt(request, 41, 1));
	EXPECT_TRUE(FTP_Free(request));
}

test_SQL_PrepareStatement()
{
	expectedFields = [];
	expectedFields[0] = "name";
	expectedFields[1] = "player";
	expectedFields[2] = "xp";
	expectedFields[3] = "level";
	expectedFields[4] = "prestige";

	expectedRow = [];
	expectedRow[0] = "Iswenzz";
	expectedRow[1] = "12345678";
	expectedRow[2] = 1296000;
	expectedRow[3] = 80;
	expectedRow[4] = 10;

	// Delete
	request = SQL_Prepare("DELETE FROM ranks WHERE player = ?");
	SQL_BindParam(request, "12345678", level.MYSQL_TYPE_STRING);
	EXPECT_TRUE(SQL_Execute(request));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(SQL_Free(request));

	// Insert
	request = SQL_Prepare("INSERT INTO ranks (name, player, xp, level, prestige) VALUES (?, ?, ?, ?, ?)");
	SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_STRING);
	SQL_BindParam(request, "12345678", level.MYSQL_TYPE_STRING);
	SQL_BindParam(request, 1296000, level.MYSQL_TYPE_LONG);
	SQL_BindParam(request, 80, level.MYSQL_TYPE_LONG);
	SQL_BindParam(request, 10, level.MYSQL_TYPE_LONG);
	EXPECT_TRUE(SQL_Execute(request));
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_EQ(SQL_AffectedRows(request), 1);
	EXPECT_TRUE(SQL_Free(request));

	// Select
	request = SQL_Prepare("SELECT name, player, xp, level, prestige FROM ranks WHERE player = ?");
	SQL_BindParam(request, "12345678", level.MYSQL_TYPE_STRING);
	EXPECT_TRUE(SQL_Execute(request));
	EXPECT_EQ(AsyncWait(request), 2);
	fields = SQL_FetchFields(request);
	rows = SQL_FetchRows(request);

	for (i = 0; i < fields.size; i++)
		EXPECT_EQ(fields[i], expectedFields[i]);
	EXPECT_EQ(SQL_NumFields(request), 5);

	EXPECT_EQ(SQL_NumRows(request), 1);
	for (i = 0; i < rows.size; i++)
	{
		row = rows[i];
		for (j = 0; j < row.size; j++)
			EXPECT_EQ(row[j], expectedRow[j]);
	}
	EXPECT_TRUE(SQL_Free(request));

	// Select
	request = SQL_Prepare("SELECT name, player, xp, level, prestige FROM ranks WHERE player = ?");
	SQL_BindParam(request, "12345678", level.MYSQL_TYPE_STRING);
	EXPECT_TRUE(SQL_Execute(request));
	EXPECT_EQ(AsyncWait(request), 2);
	fields = SQL_FetchFields(request);
	rows = SQL_FetchRowsDict(request);

	for (i = 0; i < fields.size; i++)
		EXPECT_EQ(fields[i], expectedFields[i]);
	EXPECT_EQ(SQL_NumFields(request), 5);

	EXPECT_EQ(SQL_NumRows(request), 1);
	for (i = 0; i < rows.size; i++)
	{
		row = rows[i];
		keys = Reverse(getArrayKeys(row));

		for (j = 0; j < row.size; j++)
			EXPECT_EQ(row[keys[j]], expectedRow[j]);
	}
	EXPECT_TRUE(SQL_Free(request));
}

test_SQL_Query()
{
	expectedFields = [];
	expectedFields[0] = "name";
	expectedFields[1] = "player";
	expectedFields[2] = "xp";
	expectedFields[3] = "level";
	expectedFields[4] = "prestige";

	expectedRow = [];
	expectedRow[0] = "Iswenzz";
	expectedRow[1] = "12345678";
	expectedRow[2] = 1296000;
	expectedRow[3] = 80;
	expectedRow[4] = 10;

	// Delete
	request = SQL_Query("DELETE FROM ranks WHERE player = '12345678'");
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_TRUE(SQL_Free(request));

	// Insert
	request = SQL_Query("INSERT INTO ranks (name, player, xp, level, prestige) VALUES ('Iswenzz', '12345678', 1296000, 80, 10)");
	EXPECT_EQ(AsyncWait(request), 2);
	EXPECT_EQ(SQL_AffectedRows(request), 1);
	EXPECT_TRUE(SQL_Free(request));

	// Select
	request = SQL_Query("SELECT name, player, xp, level, prestige FROM ranks WHERE player = '12345678'");
	EXPECT_EQ(AsyncWait(request), 2);
	fields = SQL_FetchFields(request);
	rows = SQL_FetchRowsDict(request);

	for (i = 0; i < fields.size; i++)
		EXPECT_EQ(fields[i], expectedFields[i]);
	EXPECT_EQ(SQL_NumFields(request), 5);

	EXPECT_EQ(SQL_NumRows(request), 1);
	for (i = 0; i < rows.size; i++)
	{
		row = rows[i];
		keys = Reverse(getArrayKeys(row));

		for (j = 0; j < row.size; j++)
			EXPECT_EQ(row[keys[j]], expectedRow[j]);
	}
	EXPECT_TRUE(SQL_Free(request));
}

test_SQL_HexString()
{
	EXPECT_EQ(SQL_HexString("Iswenzz"), "497377656E7A7A");
}

test_SQL_EscapeString()
{
	EXPECT_EQ(SQL_EscapeString("\\"), "\\\\");
}

test_SQL_SelectDB()
{
	EXPECT_TRUE(SQL_SelectDB("speedrun"));
}

test_SQL_ListDB()
{
	EXPECT_GE(SQL_ListDB().size, 1);
}

test_SQL_ListTables()
{
	EXPECT_TRUE(SQL_SelectDB("speedrun"));
	EXPECT_GE(SQL_ListTables().size, 1);
}

test_SQL_Version()
{
	EXPECT_EQ(SQL_Version(), "1.1");
}
