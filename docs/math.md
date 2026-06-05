# Math

Extended trigonometric and arithmetic functions not available in stock GSC.

## Functions

- [fmod](#fmod)
- [sin1](#sin1)
- [asin1](#asin1)
- [cos1](#cos1)
- [acos1](#acos1)
- [tan1](#tan1)
- [atan1](#atan1)
- [atan2](#atan2)

---

### `fmod(<x>, <y>)`

Returns the floating-point remainder of `x / y`.

| Parameter | Type | Description |
|-----------|------|-------------|
| `x` | float | Dividend |
| `y` | float | Divisor |

```c
r = fmod(9, 2); // 1
```

---

### `sin1(<x>)`

Returns the sine of `x` radians.

| Parameter | Type | Description |
|-----------|------|-------------|
| `x` | float | Angle in radians |

```c
s = sin1(0.4);
```

---

### `asin1(<x>)`

Returns the arc sine of `x` in radians.

| Parameter | Type | Description |
|-----------|------|-------------|
| `x` | float | Value in the range `[-1, 1]` |

```c
a = asin1(0.4);
```

---

### `cos1(<x>)`

Returns the cosine of `x` radians.

| Parameter | Type | Description |
|-----------|------|-------------|
| `x` | float | Angle in radians |

```c
c = cos1(0.4);
```

---

### `acos1(<x>)`

Returns the arc cosine of `x` in radians.

| Parameter | Type | Description |
|-----------|------|-------------|
| `x` | float | Value in the range `[-1, 1]` |

```c
a = acos1(0.4);
```

---

### `tan1(<x>)`

Returns the tangent of `x` radians.

| Parameter | Type | Description |
|-----------|------|-------------|
| `x` | float | Angle in radians |

```c
t = tan1(0.4);
```

---

### `atan1(<x>)`

Returns the arc tangent of `x` in radians.

| Parameter | Type | Description |
|-----------|------|-------------|
| `x` | float | Input value |

```c
a = atan1(0.4);
```

---

### `atan2(<y>, <x>)`

Returns the arc tangent of `y / x` in radians, using the signs of both arguments to determine the correct quadrant.

| Parameter | Type | Description |
|-----------|------|-------------|
| `y` | float | Numerator |
| `x` | float | Denominator |

```c
a = atan2(9, 2);
```
