# MySQL

#### ``SQL_Version()``
Print information about the MySQL client.

Usage Example:
```c
SQL_Version();
```
<hr>

#### ``SQL_Connect(<host>, <port>, <user>, <password>)``
Connect to a MySQL server.

Usage Example:
```c
SQL_Connect("127.0.0.1", 3306, "root", "rootpassword");
```
<hr>

#### ``SQL_Close()``
Close the MySQL connection.

Usage Example:
```c
SQL_Close();
```
<hr>

#### ``SQL_EscapeString(<string>)``
Prepends backslashes to the following characters: \x00 , \n , \r , \ , ' , " and \x1a . This function must always (with few exceptions) be used to make data safe before sending a query to MySQL.

Usage Example:
```c
SQL_EscapeString("\\");
```
<hr>

#### ``SQL_HexString(<string>)``
Return a hex representation of the string.

Usage Example:
```c
hex = SQL_HexString("Iswenzz");
```
<hr>

#### ``SQL_SelectDB(<db name>)``
Select a MySQL database.

Usage Example:
```c
SQL_SelectDB("testdb");
```
<hr>

#### ``SQL_Query(<query string>)``
Command for performing a statement on the database server.

Usage Example:
```c
SQL_Query("SELECT * FROM players");
```
<hr>

#### ``SQL_NumRows()``
Return the number of rows after a SELECT query.

Usage Example:
```c
count = SQL_NumRows();
```
<hr>

#### ``SQL_NumFields()``
Return the number of fields after a SELECT query.

Usage Example:
```c
count = SQL_NumFields();
```
<hr>

#### ``SQL_AffectedRows()``
Return the number of affected rows after a query.

Usage Example:
```c
count = SQL_AffectedRows();
```
<hr>

#### ``SQL_FetchRows()``
Retrieve rows data in a two dimensional GSC array after a query.

Usage Example:
```c
rows = SQL_FetchRows();
if (isDefined(rows) && isDefined(rows.size))
{
    for (i = 0; i < rows.size; i++)
    {
        if (isDefined(rows[i]) && isDefined(rows[i].size))
        {
            for (j = 0; j < rows[i].size; j++)
                comPrintF(rows[i][j]);
        }
    }
}
```
<hr>

#### ``SQL_FetchRow()``
Retrieve a single row data in a GSC array after a query.

Usage Example:
```c
row = SQL_FetchRow();
for (i = 0; i < row.size; i++)
    comPrintF(row[i]);
```
<hr>

#### ``SQL_FetchFields()``
Retrieve all fields in a GSC array after a query.

Usage Example:
```c
array = SQL_FetchFields();
```
<hr>

#### ``SQL_ListDB()``
Get all database names.

Usage Example:
```c
array = SQL_ListDB();
```
<hr>

#### ``SQL_ListTables()``
Get all table names.

Usage Example:
```c
array = SQL_ListTables();
```
<hr>
