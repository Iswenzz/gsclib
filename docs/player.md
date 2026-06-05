# Player

Client method extensions for reading and controlling player movement state.

All functions are called as methods on a player entity: `player FunctionName()`.

## Functions

- [GetForwardMove](#getforwardmove)
- [GetIP](#getip)
- [GetJumpOrigin](#getjumporigin)
- [GetRightMove](#getrightmove)
- [PmFlags](#pmflags)
- [PmTime](#pmtime)
- [PmType](#pmtype)
- [SetPmFlags](#setpmflags)
- [SetPmTime](#setpmtime)
- [WeaponFlags](#weaponflags)

---

### `<client> GetForwardMove()`

Returns the player's current forward movement input state.

```c
forwardMove = player GetForwardMove();
```

---

### `<client> GetIP()`

Returns the client's IP address as a string.

```c
ip = player GetIP();
```

---

### `<client> GetJumpOrigin()`

Returns the Z coordinate of the player's position at the time they jumped.

```c
jumpOrigin = player GetJumpOrigin();
```

---

### `<client> GetRightMove()`

Returns the player's current right/strafe movement input state.

```c
rightMove = player GetRightMove();
```

---

### `<client> PmFlags()`

Returns the player's current movement flags bitmask.

```c
flags = player PmFlags();
```

---

### `<client> PmTime()`

Returns the player's current movement time value.

```c
time = player PmTime();
```

---

### `<client> PmType()`

Returns the player's current movement type.

```c
type = player PmType();
```

---

### `<client> SetPmFlags(<flags>)`

Sets the player's movement flags bitmask.

| Parameter | Type | Description |
|-----------|------|-------------|
| `flags` | int | Movement flags bitmask |

```c
player SetPmFlags(flags);
```

---

### `<client> SetPmTime(<time>)`

Sets the player's movement time value.

| Parameter | Type | Description |
|-----------|------|-------------|
| `time` | int | Movement time value |

```c
player SetPmTime(time);
```

---

### `<client> WeaponFlags()`

Returns the player's current weapon flags bitmask.

```c
flags = player WeaponFlags();
```
