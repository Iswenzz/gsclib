# Extensions

#### ``Scr_AllocArray(int length)``
Create a new GSC array with a fixed size.
The array can be freed with Scr_FreeArray.

```c
VariableValueArray array = Scr_AllocArray(5);
Scr_FreeArray(&array);
```
<hr>

#### ``Scr_FreeArray(VariableValueArray *array)``
Free the value obtained by Scr_GetArray.

```c
Scr_FreeArray(&array);
```
<hr>

#### ``Scr_GetArray(uin32_t paramnum)``
Returns a GSC array based on the passed index value, which represents the GSC parameter number in which this array will be passed.

```c
VariableValueArray array = Scr_GetArray(0);
Scr_FreeArray(&array);
```
<hr>

#### ``Scr_GetFunction(uin32_t paramnum)``
Returns a GSC function id based on the passed index value.

```c
const int threadId = Scr_GetFunction(0);
```
<hr>

#### ``Scr_AddVariable(VariableValue var)``
Returns a generic variable to GSC.

```c
VariableValueArray array = Scr_GetArray(0);
Scr_AddVariable(array.items[0]);
Scr_FreeArray(&array);
```
<hr>

#### ``Scr_AddPointerArray(VariableValue var)``
Returns a GSC pointer to array.

```c
VariableValue* array = Scr_SelectParam(0);
Scr_AddPointerArray(array);
```
<hr>

#### ``Scr_GetThreadReturn()``
Returns a GSC thread return value.

```c
const uint32_t threadId = Plugin_Scr_GetFunction(0);
const short tid = Scr_ExecThread(threadId, 1);

int value = Scr_GetThreadReturn();

Plugin_Scr_FreeThread(tid);
```
<hr>

#### ``Scr_ExecThreadResult(int callbackHook, unsigned int numArgs)``
Start a thread with the specified GSC functions and arguments count, and wait for the thread to finish.

```c
const uint32_t threadId = Plugin_Scr_GetFunction(0);
const short tid = Plugin_Scr_ExecThreadResult(threadId, 0);
```
<hr>

#### ``Scr_ReturnResult()``
Copy the GSC thread return value.

```c
const uint32_t threadId = Plugin_Scr_GetFunction(0);
const short tid = Plugin_Scr_ExecThreadResult(threadId, 0);
VariableValue var = Plugin_Scr_ReturnResult();
```
<hr>

#### ``Scr_CallFunction(void (*function)(void), ...)``
Call a function with the specified function pointer. The arguments of the GSC function can be assigned with the type macros provided in the header file.

```c
const char *str = "Test string";
Scr_CallFunction(iprintlnbold, STRING(&str));
```
<hr>

#### ``Scr_CallMethod(void (*function)(scr_entref_t), scr_entref_t ent, ...)``
Call a method on an entity with the specified function pointer. The arguments of the GSC function can be assigned with the type macros provided in the header file.

```c
float vec[3];
vec[0] = 0;
vec[1] = 180;
vec[2] = 0;
Scr_CallMethod(setPlayerAngles, VECTOR(&vec));
```
<hr>

#### ``Scr_GetArrayFlags(VariableValueArray array)``
Get type flags from a GSC array.

```c
VariableValueArray array = Scr_GetArray(0);
uint32_t flags = Scr_GetArrayFlags(array);
qboolean a = HasFlag(flags, FLAG_FLOAT);
qboolean b = IsFlag(flags, FLAG_STRING);
Scr_FreeArray(&array);
```
