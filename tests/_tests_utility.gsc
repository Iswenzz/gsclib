#include lib\gsclib\_main;

// Tests for gsclib/utility
test()
{
    comPrintF("\n[======{Utility}======]\n");

    it_GetType();
    it_Ternary();
    it_IfUndef();
    it_IsNullOrEmpty();
    it_ToUpper();
    it_ToLower();
    it_ToInt();
    it_ToFloat();
    it_ToString();
    it_IsStrNumber();
    it_IsStrVector();
    it_IsStrAlpha();
    it_IsStrFloat();
    it_RegexMatch();
    it_RegexSub();
}

it_GetType()
{
    comPrintF("\n<-------[GetType]------->\n");
    f = 1.125;
    i = 10;
    s = "test";
    v = (0, 1, 2);
    printVariable(GetType(f));
    printVariable(GetType(i));
    printVariable(GetType(s));
    printVariable(GetType(v));
}

it_Ternary()
{
    comPrintF("\n<-------[Ternary]------->\n");
    printVariable(Ternary(true, 3, 4));
    printVariable(Ternary(false, 3, 4));
}

it_IfUndef()
{
    comPrintF("\n<-------[IfUndef]------->\n");
    a = "test";
    b = undefined;
    printVariable(IfUndef(b, a));
    printVariable(IfUndef(a, a));
}

it_IsNullOrEmpty()
{
    comPrintF("\n<-------[IsNullOrEmpty]------->\n");
}

it_ToUpper()
{
    comPrintF("\n<-------[ToUpper]------->\n");
}

it_ToLower()
{
    comPrintF("\n<-------[ToLower]------->\n");
}

it_ToTitle()
{
    comPrintF("\n<-------[ToTitle]------->\n");
}

it_ToInt()
{
    comPrintF("\n<-------[ToInt]------->\n");
    printVariable(ToInt("1"));
    printVariable(ToInt(2.2));
    printVariable(ToInt((3, 3, 3)));
}

it_ToFloat()
{
    comPrintF("\n<-------[ToFloat]------->\n");
    printVariable(ToFloat("1.1"));
    printVariable(ToFloat(2.2));
    printVariable(ToFloat((3.3, 3.3, 3.3)));
}

it_ToString()
{
    comPrintF("\n<-------[ToString]------->\n");
    printVariable(ToString("1"));
    printVariable(ToString(2.2));
    printVariable(ToString((3.3, 3.3, 3.3)));
}

it_IsStrNumber()
{
    comPrintF("\n<-------[IsStrNumber]------->\n");
}

it_IsStrVector()
{
    comPrintF("\n<-------[IsStrVector]------->\n");
}

it_IsStrAlpha()
{
    comPrintF("\n<-------[IsStrAlpha]------->\n");
}

it_IsStrFloat()
{
    comPrintF("\n<-------[IsStrFloat]------->\n");
}

it_RegexMatch()
{
    comPrintF("\n<-------[RegexMatch]------->\n");
}

it_RegexSub()
{
    comPrintF("\n<-------[RegexSub]------->\n");
}
