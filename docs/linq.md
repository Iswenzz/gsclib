# Language Integrated Query (LINQ)

#### `Select(<array>, <delegate>)`

Project data in a collection using delegates, the same way select clause in a SQL database to fetch specific columns of a table.

```c
new_array = Select(array, ::delegate);
```

<hr>

#### `Foreach(<array>, <delegate>)`

Executes a provided function for each array element.

```c
Foreach(players, ::heal);
```

<hr>

#### `Aggregate(<initialValue>, <array>, <delegate>)`

Aggregate the result of multiple delegate.

```c
result = Aggregate(initialValue, array, ::delegate);
```

<hr>

#### `All(<array>, <predicate>)`

Check if all items match the predicate.

```c
isAll = All(array, ::predicate);
```

<hr>

#### `Where(<array>, <predicate>)`

Reconstruct the array with only matches values from the predicate.

```c
new_array = Where(array, ::predicate);
```

<hr>

#### `Any(<array>, <predicate>)`

Check if atleast one item match the predicate.

```c
isAny = Any(array, ::predicate);
```

<hr>

#### `Last(<array>, <predicate>)`

Get the last item that match the predicate.

```c
last = Last(array, ::predicate);
```

<hr>

#### `First(<array>, <predicate>)`

Get the first item that match the predicate.

```c
first = First(array, ::predicate);
```

<hr>

#### `Count(<array>, <predicate>)`

Count all items that match the predicate.

```c
count = Count(array, ::predicate);
```

<hr>

#### `Min(<array>)`

Get the smallest value from an array of int/float/string/vector.

```c
min = Min(array);
```

<hr>

#### `Max(<array>)`

Get the biggest value from an array of int/float/string/vector.

```c
max = Max(array);
```

<hr>

#### `Cast(<array>, <type>)`

Reconstruct an array with all items casted to a specific type.
Available types are: int, float, string.

```c
strings = Cast(array, "string");
ints = Cast(array, "int");
```

<hr>

#### `OfType(<array>, <type>)`

Reconstruct the array with only the specified type.
Available types are: int, float, string.

```c
strings = OfType(array, "string");
ints = OfType(array, "int");
```

<hr>

#### `Sort(<array>)`

Sort all items from an array of int/float/string/vector.

```c
new_array = Sort(array);
```

<hr>

#### `Average(<array>)`

Get the average value from an array of int/float/vector.

```c
average = Average(array);
```

<hr>

#### `Sum(<array>)`

Adds all values from an array of int/float/vector/string.

```c
sum = Sum(array);
```

<hr>

#### `Range(<array>, <min>, <max>)`

Reconstruct the array with a specified range.

```c
new_array = Range(array, 3, 6);
```

<hr>

#### `Repeat(<array>, <repeat>)`

Repeat all values in an array.

```c
new_array = Repeat(array, 3);
```

<hr>

#### `Reverse(<array>)`

Reverse the array.

```c
new_array = Reverse(array);
```

<hr>

#### `Concat(<arraySource>, <array>)`

Concat an array with another array.

```c
new_array = Concat(arraySource, array);
```

<hr>

#### `Chunk(<array>, <count>)`

Split an array into multiple chunks.

```c
chunks = Chunk(array, 5);
```

<hr>

#### `Contains(<array>, <count>)`

Check if an array contains an element.

```c
contains = Contains(array, 5);
```

<hr>

#### `IndexOf(<array>, <element>)`

Get the index of an element.

```c
index = IndexOf(array, 10);
```

<hr>

#### `Remove(<array>, <element>)`

Remove an element from the array.

```c
newArray = Remove(array, 10);
```

<hr>

#### `RemoveAt(<array>, <element>)`

Remove an element from the array at a specific index.

```c
newArray = RemoveAt(array, 1);
```

<hr>
