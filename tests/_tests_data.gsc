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
        it_SQL_ListDB();
        it_SQL_Close();

        if (!loop)
            break;
        wait 0.05;
    }
}

it_SQL_ListDB()
{
    comPrintF("\n<-------[SQL_ListDB]------->\n");
    printArray(SQL_ListDB());
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
