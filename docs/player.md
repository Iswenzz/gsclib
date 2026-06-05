# Player

Client method extensions for reading and controlling player movement state.

All functions are called as methods on a player entity: `player FunctionName()`.

## Functions

**Info**
- [GetIP](#getip)

**Movement state**
- [GetForwardMove](#getforwardmove)
- [GetRightMove](#getrightmove)
- [GetJumpOrigin](#getjumporigin)
- [PmFlags](#pmflags)
- [SetPmFlags](#setpmflags)
- [PmTime](#pmtime)
- [SetPmTime](#setpmtime)
- [PmType](#pmtype)

**Weapon state**
- [WeaponFlags](#weaponflags)

---

### `<client> GetIP()`

Returns the client's IP address as a string.

```c
ip = player GetIP();
```

---

### `<client> GetForwardMove()`

Returns the player's current forward movement input state.

```c
forwardMove = player GetForwardMove();
```

---

### `<client> GetRightMove()`

Returns the player's current right/strafe movement input state.

```c
rightMove = player GetRightMove();
```

---

### `<client> GetJumpOrigin()`

Returns the Z coordinate of the player's position at the time they jumped.

```c
jumpOrigin = player GetJumpOrigin();
```

---

### `<client> PmFlags()`

Returns the player's current movement flags bitmask.

```c
flags = player PmFlags();
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

### `<client> PmTime()`

Returns the player's current movement time value.

```c
time = player PmTime();
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

### `<client> PmType()`

Returns the player's current movement type.

```c
type = player PmType();
```

---

### `<client> WeaponFlags()`

Returns the player's current weapon flags bitmask.

```c
flags = player WeaponFlags();
```
