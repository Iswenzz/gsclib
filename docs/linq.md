# LINQ

Array querying and transformation utilities inspired by Language Integrated Query (LINQ). All functions treat arrays as immutable — they return new arrays rather than modifying the original.

## Functions

- [Aggregate](#aggregate)
- [All](#all)
- [Any](#any)
- [Average](#average)
- [Cast](#cast)
- [Chunk](#chunk)
- [Concat](#concat)
- [Contains](#contains)
- [Count](#count)
- [First](#first)
- [Foreach](#foreach)
- [IndexOf](#indexof)
- [Last](#last)
- [Max](#max)
- [Min](#min)
- [OfType](#oftype)
- [Range](#range)
- [Remove](#remove)
- [RemoveAt](#removeat)
- [Repeat](#repeat)
- [Reverse](#reverse)
- [Select](#select)
- [Sort](#sort)
- [Sum](#sum)
- [Where](#where)

---

### `Aggregate(<initialValue>, <array>, <delegate>)`

Reduces the array to a single value by repeatedly applying the delegate. Equivalent to `reduce` in other languages.

| Parameter | Type | Description |
|-----------|------|-------------|
| `initialValue` | any | Starting value for the accumulator |
| `array` | array | The source array |
| `delegate` | function | Reducer function |

```c
result = Aggregate(0, scores, ::sum);
```
---

### `All(<array>, <predicate>)`

Returns `true` if every element satisfies the predicate.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `predicate` | function | Test function |

```c
allReady = All(players, ::isReady);
```
---

### `Any(<array>, <predicate>)`

Returns `true` if at least one element satisfies the predicate.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `predicate` | function | Test function |

```c
hasAdmin = Any(players, ::isAdmin);
```

---

### `Average(<array>)`

Returns the average value of an array of `int`, `float`, or `vector`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |

```c
avg = Average(scores);
```

---

### `Cast(<array>, <type>)`

Returns a new array with all elements converted to the given type. Valid types: `"int"`, `"float"`, `"string"`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `type` | string | Target type name |

```c
strings = Cast(numbers, "string");
ints = Cast(floats, "int");
```

---

### `Chunk(<array>, <count>)`

Splits the array into multiple sub-arrays of at most `count` elements each.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `count` | int | Maximum size of each chunk |

```c
groups = Chunk(players, 4);
```

---

### `Concat(<arraySource>, <array>)`

Returns a new array with the second array appended to the first.

| Parameter | Type | Description |
|-----------|------|-------------|
| `arraySource` | array | The first array |
| `array` | array | The array to append |

```c
all = Concat(teamA, teamB);
```

---

### `Contains(<array>, <element>)`

Returns `true` if the array contains the specified element.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `element` | any | The value to search for |

```c
if (Contains(ids, player.guid))
{
    // ...
}
```

---

### `Count(<array>, <predicate>)`

Returns the number of elements that satisfy the predicate.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `predicate` | function | Test function |

```c
aliveCount = Count(players, ::isAlive);
```

---

### `First(<array>, <predicate>)`

Returns the first element that satisfies the predicate.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `predicate` | function | Test function |

```c
host = First(players, ::isHost);
```

---

### `Foreach(<array>, <delegate>)`

Calls the delegate function once for each element in the array.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `delegate` | function | Function to call for each element |

```c
Foreach(players, ::heal);
```

---

### `IndexOf(<array>, <element>)`

Returns the index of the first occurrence of the element, or `-1` if not found.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `element` | any | The value to find |

```c
index = IndexOf(names, "Iswenzz");
```

---

### `Last(<array>, <predicate>)`

Returns the last element that satisfies the predicate.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `predicate` | function | Test function |

```c
last = Last(players, ::isAlive);
```

---

### `Max(<array>)`

Returns the largest value in an array of `int`, `float`, `string`, or `vector`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |

```c
highest = Max(scores);
```

---

### `Min(<array>)`

Returns the smallest value in an array of `int`, `float`, `string`, or `vector`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |

```c
lowest = Min(scores);
```

---

### `OfType(<array>, <type>)`

Returns a new array containing only elements of the specified type. Valid types: `"int"`, `"float"`, `"string"`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `type` | string | Type name to filter by |

```c
strings = OfType(mixed, "string");
```

---

### `Range(<array>, <min>, <max>)`

Returns a new array containing only the elements between index `min` and `max` (inclusive).

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `min` | int | Start index |
| `max` | int | End index |

```c
page = Range(results, 0, 9);
```

---

### `Remove(<array>, <element>)`

Returns a new array with the first occurrence of the element removed.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `element` | any | The value to remove |

```c
updated = Remove(players, disconnectedPlayer);
```

---

### `RemoveAt(<array>, <index>)`

Returns a new array with the element at the specified index removed.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `index` | int | Index of the element to remove |

```c
updated = RemoveAt(players, 0);
```

---

### `Repeat(<array>, <count>)`

Returns a new array with all elements repeated `count` times.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `count` | int | Number of times to repeat |

```c
doubled = Repeat(items, 2);
```

---

### `Reverse(<array>)`

Returns a new array with all elements in reverse order.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |

```c
reversed = Reverse(scores);
```

---

### `Select(<array>, <delegate>)`

Returns a new array by applying the delegate to each element. Equivalent to `map` in other languages.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `delegate` | function | Projection function |

```c
names = Select(players, ::getName);
```

---

### `Sort(<array>)`

Returns a new sorted array. Works with `int`, `float`, `string`, and `vector`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |

```c
sorted = Sort(scores);
```

---

### `Sum(<array>)`

Returns the sum of all values in an array of `int`, `float`, `vector`, or `string`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |

```c
total = Sum(scores);
```

---

### `Where(<array>, <predicate>)`

Returns a new array containing only elements for which the predicate returns `true`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `array` | array | The source array |
| `predicate` | function | Filter function |

```c
alive = Where(players, ::isAlive);
```
