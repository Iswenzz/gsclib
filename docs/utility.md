# Utility

General-purpose helpers for string formatting, type conversion, type checking, and color math.

## Functions

**Output**
- [ComPrint](#comprint)
- [ComPrintLn](#comprintln)
- [SysPrint](#sysprint)
- [SysPrintLn](#sysprintln)

**Strings**
- [fmt](#fmt)
- [Trim](#trim)
- [Replace](#replace)
- [StartsWith](#startswith)
- [EndsWith](#endswith)
- [StrJoin](#strjoin)
- [PathJoin](#pathjoin)
- [IsNullOrEmpty](#isnullorempty)
- [IsStringAlpha](#isstringalpha)
- [IsStringInt](#isstringint)
- [IsStringFloat](#isstringfloat)

**Type conversion**
- [ToString](#tostring)
- [ToInt](#toint)
- [ToFloat](#tofloat)
- [GetType](#gettype)

**Control flow**
- [Ternary](#ternary)
- [IfUndef](#ifundef)

**Color**
- [ToRGB](#torgb)
- [HexToRGB](#hextorgb)

---

### `ComPrint(<fmt>, <?arguments...>)`

Prints a formatted message to the server console.

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | string | Format string (printf-style) |
| `arguments` | any | Optional format arguments |

```c
ComPrint("Hello World!");
ComPrint("Player: %s", player.name);
```

---

### `ComPrintLn(<fmt>, <?arguments...>)`

Prints a formatted message followed by a newline to the server console. Call with no arguments to print a blank line.

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | string | Format string (printf-style) |
| `arguments` | any | Optional format arguments |

```c
ComPrintLn("Player: %s", player.name);
ComPrintLn(); // blank line
```

---

### `SysPrint(<fmt>, <?arguments...>)`

Prints a formatted message to the system output (stdout).

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | string | Format string (printf-style) |
| `arguments` | any | Optional format arguments |

```c
SysPrint("Hello World!");
SysPrint("Player: %s", player.name);
```

---

### `SysPrintLn(<fmt>, <?arguments...>)`

Prints a formatted message followed by a newline to the system output. Call with no arguments to print a blank line.

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | string | Format string (printf-style) |
| `arguments` | any | Optional format arguments |

```c
SysPrintLn("Player: %s", player.name);
SysPrintLn(); // blank line
```

---

### `fmt(<string>, <?arguments...>)`

Returns a formatted string. Equivalent to `sprintf` in C.

| Parameter | Type | Description |
|-----------|------|-------------|
| `string` | string | Format string (printf-style) |
| `arguments` | any | Optional format arguments |

```c
s = fmt("%s has rank %d", player.name, rank);
```

---

### `Trim(<string>)`

Returns a copy of the string with leading and trailing whitespace removed.

| Parameter | Type | Description |
|-----------|------|-------------|
| `string` | string | The string to trim |

```c
clean = Trim("  hello world  "); // "hello world"
```

---

### `Replace(<source>, <search>, <replace>)`

Returns a copy of `source` with all occurrences of `search` replaced by `replace`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `source` | string | The original string |
| `search` | string | The substring to find |
| `replace` | string | The replacement string |

```c
result = Replace("SR Speedrun", "Speedrun", "Deathrun"); // "SR Deathrun"
```

---

### `StartsWith(<string>, <value>)`

Returns `true` if `string` begins with `value`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `string` | string | The string to test |
| `value` | string | The prefix to check for |

```c
if (StartsWith(command, "!"))
{
    // handle command
}
```

---

### `EndsWith(<string>, <value>)`

Returns `true` if `string` ends with `value`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `string` | string | The string to test |
| `value` | string | The suffix to check for |

```c
if (EndsWith(filename, ".gsc"))
{
    // handle script file
}
```

---

### `StrJoin(<array>, <separator>)`

Joins all elements of a string array into a single string, separated by `separator`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | Array of strings |
| `separator` | string | String to insert between elements |

```c
result = StrJoin(names, ", "); // "Alice, Bob, Charlie"
```

---

### `PathJoin(<paths...>)`

Joins path segments into a single filepath string, handling separators correctly.

| Parameter | Type | Description |
|-----------|------|-------------|
| `paths` | string | One or more path segments |

```c
path = PathJoin("C:\\home", "cod4", "speedrun");
path = PathJoin("/home", "cod4", "speedrun");
```

---

### `IsNullOrEmpty(<str>)`

Returns `true` if the string is undefined or an empty string.

| Parameter | Type | Description |
|-----------|------|-------------|
| `str` | string | The value to check |

```c
if (IsNullOrEmpty(player.name))
    player.name = "Unknown";
```

---

### `IsStringAlpha(<str>)`

Returns `true` if the string contains only alphanumeric characters.

| Parameter | Type | Description |
|-----------|------|-------------|
| `str` | string | The string to test |

```c
IsStringAlpha("abc123"); // true
IsStringAlpha("abc!"); // false
```

---

### `IsStringInt(<str>)`

Returns `true` if the string represents a valid integer.

| Parameter | Type | Description |
|-----------|------|-------------|
| `str` | string | The string to test |

```c
IsStringInt("42");    // true
IsStringInt("3.14");  // false
```

---

### `IsStringFloat(<str>)`

Returns `true` if the string represents a valid floating-point number.

| Parameter | Type | Description |
|-----------|------|-------------|
| `str` | string | The string to test |

```c
IsStringFloat("3.14"); // true
IsStringFloat("abc");  // false
```

---

### `ToString(<var>)`

Converts an `int`, `float`, or `vector` to a string.

| Parameter | Type | Description |
|-----------|------|-------------|
| `var` | int \| float \| vector | The value to convert |

```c
s = ToString(player.velocity);
```

---

### `ToInt(<var>)`

Converts a `string`, `float`, or `vector` to an integer.

| Parameter | Type | Description |
|-----------|------|-------------|
| `var` | string \| float \| vector | The value to convert |

```c
i = ToInt("42");
```

---

### `ToFloat(<var>)`

Converts a `string`, `int`, or `vector` to a float.

| Parameter | Type | Description |
|-----------|------|-------------|
| `var` | string \| int \| vector | The value to convert |

```c
f = ToFloat("3.14");
```

---

### `GetType(<var>)`

Returns the type name of a GSC variable as a string.

| Parameter | Type | Description |
|-----------|------|-------------|
| `var` | any | The variable to inspect |

```c
type = GetType(player.name); // "string"
```

---

### `Ternary(<condition>, <true>, <false>)`

Returns `true` if `condition` is truthy, otherwise returns `false`. Equivalent to the `? :` operator in C.

| Parameter | Type | Description |
|-----------|------|-------------|
| `condition` | any | The condition to evaluate |
| `true` | any | Value returned when condition is truthy |
| `false` | any | Value returned when condition is falsy |

```c
score = Ternary(player.name == "Iswenzz", 1000, 0);
```

---

### `IfUndef(<var>, <default>)`

Returns `var` if it is defined, otherwise returns `default`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `var` | any | The variable to check |
| `default` | any | Fallback value if `var` is undefined |

```c
name = IfUndef(player.name, "Unknown");
```

---

### `ToRGB(<r>, <g>, <b>)`

Converts 0–255 RGB channel values to a normalized `(0.0–1.0)` vector for use with GSC color functions.

| Parameter | Type | Description |
|-----------|------|-------------|
| `r` | int | Red channel (0–255) |
| `g` | int | Green channel (0–255) |
| `b` | int | Blue channel (0–255) |

```c
color = ToRGB(255, 128, 0);
```

---

### `HexToRGB(<hex>)`

Converts a hex color string to a normalized `(0.0–1.0)` RGB vector. Accepts both `#RRGGBB` and `RRGGBB` formats.

| Parameter | Type | Description |
|-----------|------|-------------|
| `hex` | string | Hex color string |

```c
color = HexToRGB("#FF8800");
color = HexToRGB("FF8800");
```
