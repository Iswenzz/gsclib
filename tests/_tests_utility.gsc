#include sr\tests\gsclib\_main;

// Tests for gsclib/utility
test(loop)
{
	comPrintF("\n[======{Utility}======]\n");

	while (true)
	{
		it_GetType();
		it_Ternary();
		it_IfUndef();

		it_ToInt();
		it_ToFloat();
		it_ToString();

		it_ToUpper();
		it_IsNullOrEmpty();
		it_IsStringInt();
		it_IsStringAlpha();
		it_IsStringFloat();
		it_ToRGB();
		it_HexToRGB();

		if (!loop)
			break;
		wait 0.05;
	}
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
	a = undefined;
	b = "";
	c = "test";
	printVariable(IsNullOrEmpty(a));
	printVariable(IsNullOrEmpty(b));
	printVariable(IsNullOrEmpty(c));
}

it_ToUpper()
{
	comPrintF("\n<-------[ToUpper]------->\n");
	printVariable(ToUpper("test"));
	printVariable(ToUpper("test2"));
	printVariable(ToUpper("test__test"));
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

it_IsStringInt()
{
	comPrintF("\n<-------[IsStringInt]------->\n");
	printVariable(IsStringInt("123"));
	printVariable(IsStringInt("123__"));
	printVariable(IsStringInt("123.123"));
	printVariable(IsStringInt("ab123__"));
	printVariable(IsStringInt("test"));
}

it_IsStringAlpha()
{
	comPrintF("\n<-------[IsStringAlpha]------->\n");
	printVariable(IsStringAlpha("123"));
	printVariable(IsStringAlpha("123__"));
	printVariable(IsStringAlpha("123.123"));
	printVariable(IsStringAlpha("ab123__"));
	printVariable(IsStringAlpha("test"));
}

it_IsStringFloat()
{
	comPrintF("\n<-------[IsStringFloat]------->\n");
	printVariable(IsStringFloat("123.123"));
	printVariable(IsStringFloat("123.123__"));
	printVariable(IsStringFloat("123"));
	printVariable(IsStringFloat("ab123.123__"));
	printVariable(IsStringFloat("test"));
}

it_ToRGB()
{
	comPrintF("\n<-------[ToRGB]------->\n");
	printVariable(ToRGB(125, 125, 255));
}

it_HexToRGB()
{
	comPrintF("\n<-------[HexToRGB]------->\n");
	printVariable(HexToRGB("AABBCC"));
	printVariable(HexToRGB("#AABBCC"));
	printVariable(HexToRGB("#FFFFFF"));
}
