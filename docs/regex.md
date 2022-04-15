# Regular Expression (PCRE2 RegEx)

#### ``RegexMatch(<input>, <regex>)``
Get all matches in an array from the specified input string and regex.

```c
RegexMatch("hello123world456", "\\d+");
```
```c
["123", "456"]
```
<hr>

#### ``RegexSplit(<input>, <regex>)``
Get all splited string in an array from the specified input string and regex.

```c
RegexSplit("hello123world456", "\\d+");
```
```c
["hello", "world"]
```
<hr>

#### ``RegexReplace(<input>, <replace>, <regex>)``
Replace all matches with a specific string.

```c
RegexReplace("123hello456world789", "_", "\\d+");
```
```c
_hello_world_
```
<hr>
