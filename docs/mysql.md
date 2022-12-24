# MySQL

### WARNING: **Requests are not thread safe, you'll need your own scripts in GSC to handle one request at a time !**

## Example
```c
request = SQL_Prepare("SELECT name, guid, rank FROM speedrun_ranks WHERE name = ?");
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
SQL_BindResult(request, level.MYSQL_TYPE_VAR_STRING, 60);
SQL_BindResult(request, level.MYSQL_TYPE_VAR_STRING, 60);
SQL_BindResult(request, level.MYSQL_TYPE_LONG);
SQL_Execute(request);

while (AsyncStatus(request) <= 1)
	wait 0.05;

rows = SQL_FetchRowsDict(request);
for (i = 0; i < rows.size; i++)
{
	row = rows[i];

	player = row["guid"];
	rank = row["rank"];
}
SQL_Free(request);
```

### MySQL types for prepared statement:
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

#### ``SQL_Version()``
Print information about the MySQL client.

```c
SQL_Version();
```
<hr>

#### ``SQL_Connect(<host>, <port>, <user>, <password>)``
Connect to a MySQL server.

```c
SQL_Connect("127.0.0.1", 3306, "root", "rootpassword");
```
<hr>

#### ``SQL_Close()``
Close the MySQL connection.

```c
SQL_Close();
```
<hr>

#### ``SQL_Free(<request>)``
Free a MySQL Request, this must be called after being done with the query/prepare request.

```c
SQL_Close(request);
```
<hr>

#### ``SQL_EscapeString(<string>)``
Prepends backslashes to the following characters: \x00 , \n , \r , \ , ' , " and \x1a . This function must always (with few exceptions) be used to make data safe before sending a query to MySQL.

```c
SQL_EscapeString("\\");
```
<hr>

#### ``SQL_HexString(<string>)``
Return a hex representation of the string.

```c
hex = SQL_HexString("Iswenzz");
```
<hr>

#### ``SQL_SelectDB(<db name>)``
Select a MySQL database.

```c
SQL_SelectDB("testdb");
```
<hr>

#### ``SQL_Query(<query string>)``
Command for performing a query on the database server.
The request should be freed when done using SQL_Free.

```c
request = SQL_Query("SELECT * FROM players");
```
<hr>

#### ``SQL_Prepare(<query string>)``
Command for performing a statement on the database server, binds must be set in order.
The request should be freed when done using SQL_Free.

```c
request = SQL_Prepare("SELECT name, guid, rank FROM speedrun_ranks WHERE name = ?");
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
SQL_BindResult(request, level.MYSQL_TYPE_VAR_STRING, 60);
SQL_BindResult(request, level.MYSQL_TYPE_VAR_STRING, 60);
SQL_BindResult(request, level.MYSQL_TYPE_LONG);
SQL_BindResult(request, level.MYSQL_TYPE_LONG);
SQL_BindResult(request, level.MYSQL_TYPE_LONG);
SQL_Execute(request);
```
```c
request = SQL_Prepare("INSERT INTO speedrun_ranks (name, guid, rank) VALUES (?, ?, ?)");
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
SQL_BindParam(request, "313354b4", level.MYSQL_TYPE_VAR_STRING);
SQL_BindParam(request, "80", level.MYSQL_TYPE_LONG);
SQL_Execute(request);
```
<hr>

#### ``SQL_BindParam(<request>, <value>, <type>)``
Bind a value in the prepared statement.

```c
SQL_BindParam(request, "Iswenzz", level.MYSQL_TYPE_VAR_STRING);
```
<hr>

#### ``SQL_BindResult(<request>, <type>, <?string length>)``
Bind a result in the prepared statement, if you want to retrieve the col when fetching rows.
The <?string length> is optional for all types except strings where you have to specify the string length.

```c
SQL_BindResult(request, level.MYSQL_TYPE_VAR_STRING, 60);
SQL_BindResult(request, level.MYSQL_TYPE_LONG);
```
<hr>

#### ``SQL_Execute(<request>)``
Executes the prepared statement.

```c
SQL_Execute(request);
```
<hr>

#### ``SQL_NumRows(<request>)``
Return the number of rows after a query or statement.

```c
count = SQL_NumRows(request);
```
<hr>

#### ``SQL_NumFields(<request>)``
Return the number of fields after a query or statement.

```c
count = SQL_NumFields(request);
```
<hr>

#### ``SQL_AffectedRows(<request>)``
Return the number of affected rows after a query or statement.

```c
count = SQL_AffectedRows(request);
```
<hr>

#### ``SQL_FetchRows(<request>)``
Retrieve rows data in a two dimensional GSC array after a query.

```c
rows = SQL_FetchRows(request);
if (isDefined(rows) && isDefined(rows.size))
{
    for (i = 0; i < rows.size; i++)
    {
        if (isDefined(rows[i]) && isDefined(rows[i].size))
        {
            for (j = 0; j < rows[i].size; j++)
                comPrint(rows[i][j]);
        }
    }
}
```
<hr>

#### ``SQL_FetchRowsDict(<request>)``
Retrieve rows data in a two dimensional GSC string indexed array after a query.

```c
rows = SQL_FetchRowsDict(request);
if (isDefined(rows) && isDefined(rows.size))
{
    for (i = 0; i < rows.size; i++)
    {
        if (isDefined(rows[i]) && isDefined(rows[i].size))
        {
            for (j = 0; j < rows[i].size; j++)
                comPrint(rows[i][j]);
        }
    }
}
```
<hr>

#### ``SQL_FetchRow(<request>)``
Retrieve a single row data in a GSC array after a query.

```c
row = SQL_FetchRow(request);
for (i = 0; i < row.size; i++)
    comPrint(row[i]);
```
<hr>

#### ``SQL_FetchRowDict(<request>)``
Retrieve a single row data in a GSC string indexed array after a query.

```c
row = SQL_FetchRowDict(request);
for (i = 0; i < row.size; i++)
    comPrint(row[i]);
```
<hr>

#### ``SQL_FetchFields(<request>)``
Retrieve all fields in a GSC array after a query.

```c
array = SQL_FetchFields(request);
```
<hr>

#### ``SQL_ListDB()``
Get all database names.

```c
array = SQL_ListDB();
```
<hr>

#### ``SQL_ListTables()``
Get all table names.

```c
array = SQL_ListTables();
```
<hr>
