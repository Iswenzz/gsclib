# Utilities

#### ``fmt(<string>, <?arguments...>)``
Get a formatted string.

```c
a = "Iswenzz";
b = 10;

string = fmt("%s %d", a, b);
```
<hr>

#### ``ComPrintF(<fmt>, <?arguments...>)``
Print a formatted message to the console output.

```c
a = "Iswenzz";

ComPrintF("Hello World!");
ComPrintF("Hello %s!", a);
```
<hr>

#### ``ComPrintLn(<fmt>, <?arguments...>)``
Print a formatted message on a new line to the console output.

```c
a = "Iswenzz";

ComPrintLn("Hello World!");
ComPrintLn("Hello %s!", a);
ComPrintLn();
```
<hr>

#### ``GetSysTime()``
Get the system time in milliseconds.

```c
time = GetSysTime();
```
<hr>

#### ``Ternary(<condition>, <true>, <false>)``
Check the condition and return the 1st value if true or the second value if false.

```c
a = Ternary(player.name == "Iswenzz", 1000, 0);
```
<hr>

#### ``IfUndef(<var>, <default>)``
Give a default value if the variable is undefined.

```c
name = IfUndef(player.name, "Unknown player");
```
<hr>

#### ``GetType(<var>)``
Get the type name of a GSC variable.

```c
type = GetType(player.name);
```
<hr>

#### ``ToString(<var>)``
Convert int, float, vector to string.

```c
str = ToString(player.velocity);
```
<hr>

#### ``ToInt(<var>)``
Convert string, float, vector to integer.

```c
i = ToInt("123");
```
<hr>

#### ``ToFloat(<var>)``
Convert string, int, vector to float.

```c
f = ToFloat("1.23");
```
<hr>

#### ``IsNullOrEmpty(<str>)``
Check if a string is undefined or empty.

```c
IsNullOrEmpty(player.name);
```
<hr>

#### ``IsStringAlpha(<str>)``
Check if a string is alphanumeric.

```c
IsStringAlpha("abc123_&");
```
<hr>

#### ``IsStringFloat(<str>)``
Check if a string contains a float.

```c
IsStringFloat("123.123");
```
<hr>

#### ``IsStringInt(<str>)``
Check if a string contains an integer.

```c
IsStringInt("123");
```
<hr>

#### ``ToUpper(<str>)``
Convert a string to upper case.

```c
up = ToUpper("abc");
```
<hr>

#### ``ToRGB(<r>, <g>, <b>)``
Normalize RGB vector.

```c
rgb = ToRGB(125, 255, 255);
```
<hr>

#### ``HexToRGB(<hex>)``
Convert a HEX color string to a normalized RGB vector.

```c
rgb = HexToRGB("#AABBCC");
rgb = HexToRGB("AABBCC");
```
<hr>