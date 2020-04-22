# Language Integrated Query (LINQ)

#### ``Select(<array>, <delegate>)``
Project data in a collection using delegates, the same way select clause in a SQL database to fetch specific columns of a table.

Usage Example:
```c
new_array = Select(array, ::delegate);
```
<hr>

#### ``All(<array>, <predicate>)``
Check if all items match the predicate.

Usage Example:
```c
isAll = All(array, ::predicate);
```
<hr>

#### ``Where(<array>, <predicate>)``
Reconstruct the array with only matches values from the predicate.

Usage Example:
```c
new_array = Where(array, ::predicate);
```
<hr>

#### ``Any(<array>, <predicate>)``
Check if atleast one item match the predicate.

Usage Example:
```c
isAny = Any(array, ::predicate);
```
<hr>

#### ``Last(<array>, <predicate>)``
Get the last item that match the predicate.

Usage Example:
```c
last = Last(array, ::predicate);
```
<hr>

#### ``First(<array>, <predicate>)``
Get the first item that match the predicate.

Usage Example:
```c
first = First(array, ::predicate);
```
<hr>

#### ``Count(<array>, <predicate>)``
Count all items that match the predicate.

Usage Example:
```c
count = Count(array, ::predicate);
```
<hr>

#### ``Min(<array>)``
Get the smallest value from an array of int/float/string/vector.

Usage Example:
```c
min = Min(array);
```
<hr>

#### ``Max(<array>)``
Get the biggest value from an array of int/float/string/vector.

Usage Example:
```c
max = Max(array);
```
<hr>

#### ``Cast(<array>, <type>)``
Reconstruct an array with all items casted to a specific type.
Available types are: int, float, string.

Usage Example:
```c
strings = Cast(array, "string");
ints = Cast(array, "int");
```
<hr>

#### ``OfType(<array>, <type>)``
Reconstruct the array with only the specified type.
Available types are: int, float, string.

Usage Example:
```c
strings = OfType(array, "string");
ints = OfType(array, "int");
```
<hr>

#### ``Sort(<array>)``
Sort all items from an array of int/float/string/vector.

Usage Example:
```c
new_array = Sort(array);
```
<hr>

#### ``Average(<array>)``
Get the average value from an array of int/float/vector.

Usage Example:
```c
average = Average(array);
```
<hr>

#### ``Sum(<array>)``
Adds all values from an array of int/float/vector/string.

Usage Example:
```c
sum = Sum(array);
```
<hr>

#### ``Range(<array>, <min>, <max>)``
Reconstruct the array with a specified range.

Usage Example:
```c
new_array = Range(array, 3, 6);
```
<hr>

#### ``Repeat(<array>, <repeat>)``
Repeat all values in an array.

Usage Example:
```c
new_array = Repeat(array, 3);
```
<hr>

#### ``Reverse(<array>)``
Reverse the array.

Usage Example:
```c
new_array = Reverse(array);
```
<hr>