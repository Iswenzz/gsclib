# MySQL

Functions for connecting to and querying a MySQL database server.

> **Note:** Requests are not thread safe. Wrap all MySQL calls in a [critical section](async.md).

## Functions

- [SQL_Connect](#sql_connect)
- [SQL_Close](#sql_close)
- [SQL_SelectDB](#sql_selectdb)
- [SQL_Query](#sql_query)
- [SQL_Prepare](#sql_prepare)
- [SQL_BindParam](#sql_bindparam)
- [SQL_Execute](#sql_execute)
- [SQL_Free](#sql_free)
- [SQL_FetchRow](#sql_fetchrow)
- [SQL_FetchRowDict](#sql_fetchrowdict)
- [SQL_FetchRows](#sql_fetchrows)
- [SQL_FetchRowsDict](#sql_fetchrowsdict)
- [SQL_FetchFields](#sql_fetchfields)
- [SQL_NumRows](#sql_numrows)
- [SQL_NumFields](#sql_numfields)
- [SQL_AffectedRows](#sql_affectedrows)
- [SQL_EscapeString](#sql_escapestring)
- [SQL_HexString](#sql_hexstring)
- [SQL_ListDB](#sql_listdb)
- [SQL_ListTables](#sql_listtables)
- [SQL_Version](#sql_version)

---

## Example

```c
critical_enter("mysql");

SQL_Connect("127.0.0.1", 3306, "root", "rootpassword");
SQL_SelectDB("gamedb");

request = SQL_Prepare("SELECT name, guid, rank FROM ranks WHERE name = ?");
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
SQL_Execute(request);
AsyncWait(request);

rows = SQL_FetchRowsDict(request);
for (i = 0; i < rows.size; i++)
{
    row = rows[i];
    guid = row["guid"];
    rank = row["rank"];
}
SQL_Free(request);
SQL_Close();

critical_leave("mysql");
```

---

## MySQL types

Used as the `type` parameter in `SQL_BindParam` for prepared statements.

```c
level.MYSQL_TYPE_DECIMAL      = 0;
level.MYSQL_TYPE_TINY         = 1;
level.MYSQL_TYPE_SHORT        = 2;
level.MYSQL_TYPE_LONG         = 3;
level.MYSQL_TYPE_FLOAT        = 4;
level.MYSQL_TYPE_DOUBLE       = 5;
level.MYSQL_TYPE_NULL         = 6;
level.MYSQL_TYPE_TIMESTAMP    = 7;
level.MYSQL_TYPE_LONGLONG     = 8;
level.MYSQL_TYPE_INT24        = 9;
level.MYSQL_TYPE_DATE         = 10;
level.MYSQL_TYPE_TIME         = 11;
level.MYSQL_TYPE_DATETIME     = 12;
level.MYSQL_TYPE_YEAR         = 13;
level.MYSQL_TYPE_NEWDATE      = 14;
level.MYSQL_TYPE_VARCHAR      = 15;
level.MYSQL_TYPE_BIT          = 16;
level.MYSQL_TYPE_TIMESTAMP2   = 17;
level.MYSQL_TYPE_DATETIME2    = 18;
level.MYSQL_TYPE_TIME2        = 19;
level.MYSQL_TYPE_JSON         = 245;
level.MYSQL_TYPE_NEWDECIMAL   = 246;
level.MYSQL_TYPE_ENUM         = 247;
level.MYSQL_TYPE_SET          = 248;
level.MYSQL_TYPE_TINY_BLOB    = 249;
level.MYSQL_TYPE_MEDIUM_BLOB  = 250;
level.MYSQL_TYPE_LONG_BLOB    = 251;
level.MYSQL_TYPE_BLOB         = 252;
level.MYSQL_TYPE_VAR_STRING   = 253;
level.MYSQL_TYPE_STRING       = 254;
level.MYSQL_TYPE_GEOMETRY     = 255;
```

---

### `SQL_Connect(<host>, <port>, <user>, <password>)`

Connects to a MySQL server.

| Parameter | Type | Description |
|-----------|------|-------------|
| `host` | string | Hostname or IP address |
| `port` | int | Server port (typically `3306`) |
| `user` | string | MySQL username |
| `password` | string | MySQL password |

```c
SQL_Connect("127.0.0.1", 3306, "root", "rootpassword");
```

---

### `SQL_Close()`

Closes the active MySQL connection.

```c
SQL_Close();
```

---

### `SQL_SelectDB(<name>)`

Selects the active database to use for subsequent queries.

| Parameter | Type | Description |
|-----------|------|-------------|
| `name` | string | Database name |

```c
SQL_SelectDB("gamedb");
```

---

### `SQL_Query(<query>)`

Executes a raw SQL query and returns a request handle. Free it with `SQL_Free` when done.

| Parameter | Type | Description |
|-----------|------|-------------|
| `query` | string | SQL query string |

```c
request = SQL_Query("SELECT * FROM players");
AsyncWait(request);
rows = SQL_FetchRows(request);
SQL_Free(request);
```

---

### `SQL_Prepare(<query>)`

Creates a prepared statement with `?` placeholders. Bind values with `SQL_BindParam` in order, then execute with `SQL_Execute`. Free with `SQL_Free` when done.

| Parameter | Type | Description |
|-----------|------|-------------|
| `query` | string | SQL query string with `?` placeholders |

```c
// SELECT example
request = SQL_Prepare("SELECT name, guid, rank FROM ranks WHERE name = ?");
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
SQL_Execute(request);

// INSERT example
request = SQL_Prepare("INSERT INTO ranks (name, guid, rank) VALUES (?, ?, ?)");
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
SQL_BindParam(request, "313354b4", level.MYSQL_TYPE_VAR_STRING);
SQL_BindParam(request, "80", level.MYSQL_TYPE_LONG);
SQL_Execute(request);
```

---

### `SQL_BindParam(<request>, <value>, <type>)`

Binds a value to the next `?` placeholder in a prepared statement. Call once per placeholder, in order.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A prepared statement handle |
| `value` | any | Value to bind |
| `type` | int | MySQL type constant (see [MySQL types](#mysql-types)) |

```c
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
```

---

### `SQL_Execute(<request>)`

Executes a prepared statement.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A prepared statement handle |

```c
SQL_Execute(request);
AsyncWait(request);
```

---

### `SQL_Free(<request>)`

Frees a query or prepared statement handle. Must be called after all data has been read.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
SQL_Free(request);
```

---

### `SQL_FetchRow(<request>)`

Returns the next row as an integer-indexed GSC array.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
row = SQL_FetchRow(request);
for (i = 0; i < row.size; i++)
    ComPrint(row[i]);
```

---

### `SQL_FetchRowDict(<request>)`

Returns the next row as a string-indexed GSC array (column name → value).

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
row = SQL_FetchRowDict(request);
ComPrint(row["name"]);
```

---

### `SQL_FetchRows(<request>)`

Returns all rows as a 2D integer-indexed GSC array.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
rows = SQL_FetchRows(request);
for (i = 0; i < rows.size; i++)
    for (j = 0; j < rows[i].size; j++)
        ComPrint(rows[i][j]);
```

---

### `SQL_FetchRowsDict(<request>)`

Returns all rows as a 2D string-indexed GSC array (column name → value).

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
rows = SQL_FetchRowsDict(request);
for (i = 0; i < rows.size; i++)
    ComPrint(rows[i]["name"]);
```

---

### `SQL_FetchFields(<request>)`

Returns all column names as an array of strings.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
fields = SQL_FetchFields(request);
```

---

### `SQL_NumRows(<request>)`

Returns the number of rows in the result set.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
count = SQL_NumRows(request);
```

---

### `SQL_NumFields(<request>)`

Returns the number of fields (columns) in the result set.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
count = SQL_NumFields(request);
```

---

### `SQL_AffectedRows(<request>)`

Returns the number of rows affected by an `INSERT`, `UPDATE`, or `DELETE` query.

| Parameter | Type | Description |
|-----------|------|-------------|
| `request` | handle | A request handle |

```c
count = SQL_AffectedRows(request);
```

---

### `SQL_EscapeString(<string>)`

Escapes special characters in a string to make it safe for use in a raw SQL query. Always use this before interpolating user input into a query string.

| Parameter | Type | Description |
|-----------|------|-------------|
| `string` | string | The raw string to escape |

```c
safe = SQL_EscapeString(userInput);
```

---

### `SQL_HexString(<string>)`

Returns a hex-encoded representation of the given string.

| Parameter | Type | Description |
|-----------|------|-------------|
| `string` | string | The string to encode |

```c
hex = SQL_HexString("Iswenzz");
```

---

### `SQL_ListDB()`

Returns an array of all database names on the server.

```c
databases = SQL_ListDB();
```

---

### `SQL_ListTables()`

Returns an array of all table names in the currently selected database.

```c
tables = SQL_ListTables();
```

---

### `SQL_Version()`

Prints MySQL client version information to the console.

```c
SQL_Version();
```
