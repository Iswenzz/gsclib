# Regex

Regular expression functions powered by [PCRE2](https://www.pcre.org/).

## Functions

- [RegexMatch](#regexmatch)
- [RegexSplit](#regexsplit)
- [RegexReplace](#regexreplace)

---

### `RegexMatch(<input>, <regex>)`

Returns an array of all substrings in `input` that match the pattern.

| Parameter | Type | Description |
|-----------|------|-------------|
| `input` | string | The string to search |
| `regex` | string | PCRE2 regular expression |

```c
matches = RegexMatch("hello123world456", "\\d+");
// ["123", "456"]
```

---

### `RegexSplit(<input>, <regex>)`

Splits `input` at every match of the pattern and returns an array of the parts between matches.

| Parameter | Type | Description |
|-----------|------|-------------|
| `input` | string | The string to split |
| `regex` | string | PCRE2 regular expression |

```c
parts = RegexSplit("hello123world456", "\\d+");
// ["hello", "world"]
```

---

### `RegexReplace(<input>, <replace>, <regex>)`

Replaces every match of the pattern in `input` with `replace` and returns the resulting string.

| Parameter | Type | Description |
|-----------|------|-------------|
| `input` | string | The string to modify |
| `replace` | string | Replacement string |
| `regex` | string | PCRE2 regular expression |

```c
result = RegexReplace("123hello456world789", "_", "\\d+");
// "_hello_world_"
```
