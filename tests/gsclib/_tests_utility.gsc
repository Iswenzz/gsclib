#include sr\tests\_main;

// Tests for gsclib/utility
test()
{
	suit("GSCLIB - Utility");

	run(::it_GetType, "GetType");
	run(::it_Ternary, "Ternary");
	run(::it_IfUndef, "IfUndef");

	run(::it_ToInt, "ToInt");
	run(::it_ToFloat, "ToFloat");
	run(::it_ToString, "ToString");

	run(::it_ToUpper, "ToUpper");
	run(::it_IsNullOrEmpty, "IsNullOrEmpty");
	run(::it_IsStringInt, "IsStringInt");
	run(::it_IsStringAlpha, "IsStringAlpha");
	run(::it_IsStringFloat, "IsStringFloat");
	run(::it_ToRGB, "ToRGB");
	run(::it_HexToRGB, "HexToRGB");
}

it_GetType()
{
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
	printVariable(Ternary(true, 3, 4));
	printVariable(Ternary(false, 3, 4));
}

it_IfUndef()
{
	a = "test";
	b = undefined;

	printVariable(IfUndef(b, a));
	printVariable(IfUndef(a, a));
}

it_IsNullOrEmpty()
{
	a = undefined;
	b = "";
	c = "test";

	printVariable(IsNullOrEmpty(a));
	printVariable(IsNullOrEmpty(b));
	printVariable(IsNullOrEmpty(c));
}

it_ToUpper()
{
	printVariable(ToUpper("test"));
	printVariable(ToUpper("test2"));
	printVariable(ToUpper("test__test"));
}

it_ToInt()
{
	printVariable(ToInt("1"));
	printVariable(ToInt(2.2));
	printVariable(ToInt((3, 3, 3)));
}

it_ToFloat()
{
	printVariable(ToFloat("1.1"));
	printVariable(ToFloat(2.2));
	printVariable(ToFloat((3.3, 3.3, 3.3)));
}

it_ToString()
{
	printVariable(ToString("1"));
	printVariable(ToString(2.2));
	printVariable(ToString((3.3, 3.3, 3.3)));
}

it_IsStringInt()
{
	printVariable(IsStringInt("123"));
	printVariable(IsStringInt("123__"));
	printVariable(IsStringInt("123.123"));
	printVariable(IsStringInt("ab123__"));
	printVariable(IsStringInt("test"));
}

it_IsStringAlpha()
{
	printVariable(IsStringAlpha("123"));
	printVariable(IsStringAlpha("123__"));
	printVariable(IsStringAlpha("123.123"));
	printVariable(IsStringAlpha("ab123__"));
	printVariable(IsStringAlpha("test"));
}

it_IsStringFloat()
{
	printVariable(IsStringFloat("123.123"));
	printVariable(IsStringFloat("123.123__"));
	printVariable(IsStringFloat("123"));
	printVariable(IsStringFloat("ab123.123__"));
	printVariable(IsStringFloat("test"));
}

it_ToRGB()
{
	printVariable(ToRGB(125, 125, 255));
}

it_HexToRGB()
{
	printVariable(HexToRGB("AABBCC"));
	printVariable(HexToRGB("#AABBCC"));
	printVariable(HexToRGB("#FFFFFF"));
}
