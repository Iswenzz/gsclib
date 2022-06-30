#include sr\libs\gscunit\_main;
#include sr\libs\gsclib\__test__\_suite;

main()
{
	suite("GSCLIB Net");
	setup();

	beforeAll();

	// net/curl
	it(::test_CURL_Version, "CURL_Version");
	it(::test_CURL_HeaderCleanup, "CURL_HeaderCleanup");
	it(::test_CURL_OptCleanup, "CURL_OptCleanup");
	it(::test_CURL_AddOpt, "CURL_AddOpt");

	// net/ftp
	it(::test_SFTP_Shell, "SFTP_Shell", ::beforeSFTP, ::afterSFTP);
	it(::test_SFTP_PostGetFile, "SFTP_PostGetFile", ::beforeSFTP, ::afterSFTP);
	it(::test_FTP_Shell, "FTP_Shell", ::beforeFTP, ::afterFTP);
	it(::test_FTP_PostGetFile, "FTP_PostGetFile", ::beforeFTP, ::afterFTP);

	// net/https
	it(::test_HTTPS_GetFile, "HTTPS_GetFile");
	it(::test_HTTPS_GetString, "HTTPS_GetString");
	it(::test_HTTPS_PostFile, "HTTPS_PostFile");
	it(::test_HTTPS_PostString, "HTTPS_PostString");

	// net/mysql
	it(::test_SQL_Version, "SQL_Version", ::beforeMySQL);
	it(::test_SQL_HexString, "SQL_HexString", ::beforeMySQL);
	it(::test_SQL_EscapeString, "SQL_EscapeString", ::beforeMySQL);
	it(::test_SQL_SelectDB, "SQL_SelectDB", ::beforeMySQL);
	it(::test_SQL_ListDB, "SQL_ListDB", ::beforeMySQL);
	it(::test_SQL_ListTables, "SQL_ListTables", ::beforeMySQL);
	it(::test_SQL_PrepareStatement, "SQL_PrepareStatement", ::beforeMySQL);
	it(::test_SQL_PrepareStatementDict, "SQL_PrepareStatementDict", ::beforeMySQL);
	it(::test_SQL_Query, "SQL_Query", ::beforeMySQL);

	afterAll();
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

beforeAll()
{
	if (hasMySQL())
	{
		SQL_Connect("192.168.1.86", 3306, "root", "rootpassword");
		SQL_SelectDB("speedrun");
	}
}

afterAll()
{
	if (hasMySQL())
		SQL_Close();
}

beforeMySQL()
{
	if (!hasMySQL())
		return false;
	SQL_Query("DELETE FROM ranks");
	return true;
}

beforeSFTP()
{
	if (!hasSFTP())
		return false;
	SFTP_Connect("192.168.1.86", "root", "rootpassword", 22);
	return true;
}

afterSFTP()
{
	if (!hasSFTP())
		return false;
	FTP_Close();
	return true;
}

beforeFTP()
{
	if (!hasFTP())
		return false;
	FTP_Connect("192.168.1.86", "root", "rootpassword", 21);
	return true;
}

afterFTP()
{
	if (!hasFTP())
		return false;
	FTP_Close();
	return true;
}

test_CURL_Version()
{
	EXPECT_EQ(CURL_Version(), "7.80.0");
}

test_CURL_HeaderCleanup()
{
	EXPECT_UNDEFINED(CURL_HeaderCleanup());
}

test_CURL_OptCleanup()
{
	EXPECT_UNDEFINED(CURL_OptCleanup());
}

test_CURL_AddOpt()
{
	EXPECT_UNDEFINED(CURL_AddOpt(41, 1));
}

test_HTTPS_GetFile()
{
	url = "https://iswenzz.com/";
	EXPECT_TRUE(HTTPS_GetFile("temp/iswenzz.html", url));
}

test_HTTPS_GetString()
{
	url = "http://httpbin.org/get";
	EXPECT_CONTAIN(HTTPS_GetString(url), "httpbin.org");
}

test_HTTPS_PostFile()
{
	url = "http://httpbin.org/post";
	EXPECT_CONTAIN(HTTPS_PostFile("temp/iswenzz.html", url), "Iswenzz");
	FILE_Delete("temp/iswenzz.html");
}

test_HTTPS_PostString()
{
	json = "{\"login\":\"login\",\"password\":\"password\"}";
	url = "http://httpbin.org/post";

	CURL_AddHeader("Accept: application/json,Content-Type: application/json");
	EXPECT_CONTAIN(HTTPS_PostString(json, url), "password");
}

test_SFTP_Shell()
{
	FILE_Create("temp/test.txt");
	EXPECT_TRUE(FTP_PostFile("temp/test.txt", "test.txt"));

	CURL_AddHeader("rename test.txt new.txt");
	EXPECT_TRUE(FTP_Shell());

	CURL_AddHeader("rm new.txt");
	EXPECT_TRUE(FTP_Shell());
}

test_SFTP_PostGetFile()
{
	EXPECT_TRUE(FTP_PostFile("temp/test.txt", "get.txt"));
	EXPECT_TRUE(FTP_GetFile("temp/test.txt", "get.txt"));

	CURL_AddHeader("rm get.txt");
	EXPECT_TRUE(FTP_Shell());
	FILE_Delete("temp/test.txt");
}

test_FTP_Shell()
{
	FILE_Create("temp/test.txt");
	EXPECT_TRUE(FTP_PostFile("temp/test.txt", "test.txt"));

	CURL_AddHeader("RNFR test.txt");
	CURL_AddHeader("RNTO new.txt");
	EXPECT_TRUE(FTP_Shell());

	CURL_AddHeader("DELE new.txt");
	EXPECT_TRUE(FTP_Shell());
}

test_FTP_PostGetFile()
{
	EXPECT_TRUE(FTP_PostFile("temp/test.txt", "get.txt"));
	EXPECT_TRUE(FTP_GetFile("temp/test.txt", "get.txt"));

	CURL_AddHeader("DELE get.txt");
	EXPECT_TRUE(FTP_Shell());
	FILE_Delete("temp/test.txt");
}

test_SQL_PrepareStatement()
{
	expectedFields = [];
	expectedFields[0] = "name";
	expectedFields[1] = "player";
	expectedFields[2] = "xp";
	expectedFields[3] = "rank";
	expectedFields[4] = "prestige";

	expectedRow = [];
	expectedRow[0] = "Iswenzz";
	expectedRow[1] = "05a84e1d";
	expectedRow[2] = 1296000;
	expectedRow[3] = 80;
	expectedRow[4] = 10;

	// Insert Into
	EXPECT_TRUE(SQL_Prepare("INSERT INTO ranks (name, player, xp, rank, prestige) VALUES (?, ?, ?, ?, ?)"));
	SQL_BindParam("Iswenzz", level.MYSQL_TYPE_STRING);
	SQL_BindParam("05a84e1d", level.MYSQL_TYPE_STRING);
	SQL_BindParam(1296000, level.MYSQL_TYPE_LONG);
	SQL_BindParam(80, level.MYSQL_TYPE_LONG);
	SQL_BindParam(10, level.MYSQL_TYPE_LONG);
	EXPECT_TRUE(SQL_Execute());

	EXPECT_EQ(SQL_AffectedRows(), 1);

	// Select
	EXPECT_TRUE(SQL_Prepare("SELECT name, player, xp, rank, prestige FROM ranks"));
	SQL_BindResult(level.MYSQL_TYPE_STRING, 36);
	SQL_BindResult(level.MYSQL_TYPE_STRING, 8);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	EXPECT_TRUE(SQL_Execute());

	fields = SQL_FetchFields();
	rows = SQL_FetchRows();

	for (i = 0; i < fields.size; i++)
		EXPECT_EQ(fields[i], expectedFields[i]);
	EXPECT_EQ(SQL_NumFields(), 5);

	EXPECT_EQ(SQL_NumRows(), 1);
	for (i = 0; i < rows.size; i++)
	{
		row = rows[i];
		for (j = 0; j < row.size; j++)
			EXPECT_EQ(row[j], expectedRow[j]);
	}
}

test_SQL_PrepareStatementDict()
{
	expectedFields = [];
	expectedFields[0] = "name";
	expectedFields[1] = "player";
	expectedFields[2] = "xp";
	expectedFields[3] = "rank";
	expectedFields[4] = "prestige";

	expectedRow = [];
	expectedRow[0] = "Iswenzz";
	expectedRow[1] = "05a84e1d";
	expectedRow[2] = 1296000;
	expectedRow[3] = 80;
	expectedRow[4] = 10;

	// Insert Into
	EXPECT_TRUE(SQL_Prepare("INSERT INTO ranks (name, player, xp, rank, prestige) VALUES (?, ?, ?, ?, ?)"));
	SQL_BindParam("Iswenzz", level.MYSQL_TYPE_STRING);
	SQL_BindParam("05a84e1d", level.MYSQL_TYPE_STRING);
	SQL_BindParam(1296000, level.MYSQL_TYPE_LONG);
	SQL_BindParam(80, level.MYSQL_TYPE_LONG);
	SQL_BindParam(10, level.MYSQL_TYPE_LONG);
	EXPECT_TRUE(SQL_Execute());

	EXPECT_EQ(SQL_AffectedRows(), 1);

	// Select
	EXPECT_TRUE(SQL_Prepare("SELECT name, player, xp, rank, prestige FROM ranks"));
	SQL_BindResult(level.MYSQL_TYPE_STRING, 36);
	SQL_BindResult(level.MYSQL_TYPE_STRING, 8);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	SQL_BindResult(level.MYSQL_TYPE_LONG);
	EXPECT_TRUE(SQL_Execute());

	fields = SQL_FetchFields();
	rows = SQL_FetchRowsDict();

	for (i = 0; i < fields.size; i++)
		EXPECT_EQ(fields[i], expectedFields[i]);
	EXPECT_EQ(SQL_NumFields(), 5);

	EXPECT_EQ(SQL_NumRows(), 1);
	for (i = 0; i < rows.size; i++)
	{
		row = rows[i];
		keys = Reverse(getArrayKeys(row));

		for (j = 0; j < row.size; j++)
			EXPECT_EQ(row[keys[j]], expectedRow[j]);
	}
}

test_SQL_Query()
{
	expectedFields = [];
	expectedFields[0] = "name";
	expectedFields[1] = "player";
	expectedFields[2] = "xp";
	expectedFields[3] = "rank";
	expectedFields[4] = "prestige";

	expectedRow = [];
	expectedRow[0] = "Iswenzz";
	expectedRow[1] = "05a84e1d";
	expectedRow[2] = "1296000";
	expectedRow[3] = "80";
	expectedRow[4] = "10";

	// Insert Into
	queryInsert = "INSERT INTO ranks (name, player, xp, rank, prestige) " +
		"VALUES ('Iswenzz', '05a84e1d', 1296000, 80, 10)";
	EXPECT_TRUE(SQL_Query(queryInsert));
	EXPECT_EQ(SQL_AffectedRows(), 1);

	// Select
	EXPECT_TRUE(SQL_Query("SELECT name, player, xp, rank, prestige FROM ranks"));

	fields = SQL_FetchFields();
	rows = SQL_FetchRowsDict();

	for (i = 0; i < fields.size; i++)
		EXPECT_EQ(fields[i], expectedFields[i]);
	EXPECT_EQ(SQL_NumFields(), 5);

	EXPECT_EQ(SQL_NumRows(), 1);
	for (i = 0; i < rows.size; i++)
	{
		row = rows[i];
		keys = Reverse(getArrayKeys(row));

		for (j = 0; j < row.size; j++)
			EXPECT_EQ(row[keys[j]], expectedRow[j]);
	}
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
	EXPECT_EQ(SQL_Version(), "8.0.17");
}
