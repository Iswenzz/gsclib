# Regular Expression (RegEx)

#### ``RegexMatch(<input>, <regex>)``
Get all matches in an array from the specified input string and regex.

Usage Example:
```c
RegexMatch("zzzz123affff12345ffffb", "\\d+");
/* output:
123
12345
*/
```
<hr>

#### ``RegexSplit(<input>, <regex>)``
Get all splited string in an array from the specified input string and regex.

Usage Example:
```c
RegexSplit("zzzz123affff12345ffffb", "\\d+");
/* output:
zzzz
affff
ffffb
*/
```
<hr>

#### ``RegexReplace(<input>, <replace>, <regex>)``
Replace all matches with a specific string.

Usage Example:
```c
RegexReplace("zzzz123affff12345ffffb", "", "\\d+");
/* output:
zzzzaffffffffb
*/
```
<hr>