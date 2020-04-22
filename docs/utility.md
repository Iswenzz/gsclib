# Utilities

#### ``ComPrintf(<string>)``
Print a message to the console output.

Usage Example:
```c
ComPrintf("Hello World!");
```
<hr>

#### ``Ternary(<condition>, <true>, <false>)``
Check the condition and return the 1st value if true or the second value if false.

Usage Example:
```c
a = Ternary(player.name == "Iswenzz", 1000, 0);
```
<hr>

#### ``IfUndef(<var>, <default>)``
Give a default value if the variable is undefined.

Usage Example:
```c
name = IfUndef(player.name, "Unknown player");
```
<hr>

#### ``GetType(<var>)``
Get the type name of a GSC variable.

Usage Example:
```c
type = GetType(player.name);
```
<hr>

#### ``ToString(<var>)``
Convert int, float, vector to string.

Usage Example:
```c
str = ToString(player.velocity);
```
<hr>

#### ``ToInt(<var>)``
Convert string, float, vector to integer.

Usage Example:
```c
i = ToInt("123");
```
<hr>

#### ``ToFloat(<var>)``
Convert string, int, vector to float.

Usage Example:
```c
f = ToFloat("1.23");
```
<hr>

#### ``IsNullOrEmpty(<str>)``
Check if a string is undefined or empty.

Usage Example:
```c
IsNullOrEmpty(player.name);
```
<hr>

#### ``IsStringAlpha(<str>)``
Check if a string is alphanumeric.

Usage Example:
```c
IsStringAlpha("abc123_&");
```
<hr>

#### ``IsStringFloat(<str>)``
Check if a string contains a float.

Usage Example:
```c
IsStringFloat("123.123");
```
<hr>

#### ``IsStringInt(<str>)``
Check if a string contains an integer.

Usage Example:
```c
IsStringInt("123");
```
<hr>

#### ``ToUpper(<str>)``
Convert a string to upper case.

Usage Example:
```c
up = ToUpper("abc");
```
<hr>

#### ``ToRGB(<r>, <g>, <b>)``
Normalize RGB vector.

Usage Example:
```c
rgb = ToRGB(125, 255, 255);
```
<hr>

#### ``HexToRGB(<hex>)``
Convert a HEX color string to a normalized RGB vector.

Usage Example:
```c
rgb = HexToRGB("#AABBCC");
rgb = HexToRGB("AABBCC");
```
<hr>