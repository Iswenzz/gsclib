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

        if (!loop)
            break;
        wait 0.05;
    }
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

it_SQLVersion()
{
    comPrintF("\n<-------[SQLVersion]------->\n");
    printVariable(SQLVersion());
}
