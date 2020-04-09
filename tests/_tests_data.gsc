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
        
        it_SQLVersion();
        it_SQLConnect();
        it_SQLClose();

        if (!loop)
            break;
        wait 0.05;
    }
}

it_SQLVersion()
{
    comPrintF("\n<-------[SQLVersion]------->\n");
    printVariable(SQLVersion());
}

it_SQLConnect()
{
    comPrintF("\n<-------[SQLConnect]------->\n");
    printVariable(SQLConnect("127.0.0.1", 3306, "root", "rootpassword"));
}

it_SQLClose()
{
    comPrintF("\n<-------[SQLClose]------->\n");
    printVariable(SQLClose());
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
