#include sr\tests\_main;

// Tests for gsclib/net
test()
{
	suit("GSCLIB - Net");

	run(::it_CURL_Version, "CURL_Version");
	run(::it_CURL_HeaderCleanup, "CURL_HeaderCleanup");
	run(::it_CURL_OptCleanup, "CURL_OptCleanup");
	
	run(::it_HTTPS_GetFile, "HTTPS_GetFile");
	run(::it_HTTPS_GetString, "HTTPS_GetString");
	run(::it_HTTPS_PostFile, "HTTPS_PostFile");
	run(::it_HTTPS_PostString, "HTTPS_PostString");
	
	run(::it_SFTP_Connect, "SFTP_Connect");
	run(::it_FTP_PostFile, "FTP_PostFile");
	run(::it_FTP_Shell, "FTP_Shell");
	run(::it_FTP_GetFile, "FTP_GetFile");
	run(::it_FTP_Close, "FTP_Close");
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

// Close FTP/SFTP connection.
it_FTP_Close()
{
	printVariable(FTP_Close());
}
