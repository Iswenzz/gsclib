#include sr\tests\gsclib\_main;

// Tests for gsclib/net
test(loop)
{
	comPrintF("\n[======{Net}======]\n");

	while (true)
	{
		it_CURL_Version();
		it_CURL_HeaderCleanup();
		it_CURL_OptCleanup();
		
		it_HTTPS_GetFile();
		it_HTTPS_GetString();
		it_HTTPS_PostFile();
		it_HTTPS_PostString();
		
		it_SFTP_Connect();
		it_FTP_PostFile();
		it_FTP_Shell();
		it_FTP_GetFile();
		it_FTP_Close();

		if (!loop)
			break;
		wait 0.05;
	}
}

it_CURL_Version()
{
	comPrintF("\n<-------[CURL_Version]------->\n");
	CURL_Version();
}

it_CURL_HeaderCleanup()
{
	comPrintF("\n<-------[CURL_HeaderCleanup]------->\n");
	CURL_HeaderCleanup();
}

it_CURL_OptCleanup()
{
	comPrintF("\n<-------[CURL_OptCleanup]------->\n");
	CURL_OptCleanup();
}

it_HTTPS_GetFile()
{
	comPrintF("\n<-------[HTTPS_GetFile]------->\n");
	CURL_AddOpt(41, 1);
	printVariable(HTTPS_GetFile("test/version.txt", "https://iswenzz.com:1337/speedrun_app/version.txt"));
}

it_HTTPS_GetString()
{
	comPrintF("\n<-------[HTTPS_GetString]------->\n");
	printVariable(HTTPS_GetString("http://httpbin.org/get"));
}

it_HTTPS_PostFile()
{
	comPrintF("\n<-------[HTTPS_PostFile]------->\n");
	printVariable(HTTPS_PostFile("test/version.txt", "http://httpbin.org/post"));
}

it_HTTPS_PostString()
{
	comPrintF("\n<-------[HTTPS_PostString]------->\n");
	CURL_SetHeader("Accept: application/json,Content-Type: application/json");
	printVariable(HTTPS_PostString("{\"login\":\"login\",\"password\":\"password\"}", "http://httpbin.org/post"));
}

it_SFTP_Connect()
{
	// There is FTP_Connect aswell.
	comPrintF("\n<-------[SFTP_Connect]------->\n");
	printVariable(SFTP_Connect("localhost", "root", "rootpassword", 22));
}

it_FTP_PostFile()
{
	comPrintF("\n<-------[FTP_PostFile]------->\n");
	printVariable(FTP_PostFile("libcurl.dll", "libcurl.dll"));
}

it_FTP_Shell()
{
	comPrintF("\n<-------[FTP_Shell]------->\n");
	// CURL_SetHeader("RNFR libcurl.dll,RNTO test.dll"); // FTP cmd
	CURL_SetHeader("rename libcurl.dll test.dll"); // SFTP cmd
	printVariable(FTP_Shell());
}

it_FTP_GetFile()
{
	comPrintF("\n<-------[FTP_GetFile]------->\n");
	printVariable(FTP_GetFile("test.dll", "test.dll"));
}

it_FTP_Close()
{
	// Close FTP or SFTP connection.
	comPrintF("\n<-------[FTP_Close]------->\n");
	printVariable(FTP_Close());
}
