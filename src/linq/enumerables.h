#pragma once
#include <CGSC/cgsc.h>

void GScr_LINQ_Min();
void GScr_LINQ_Max();
void GScr_LINQ_Cast();
void GScr_LINQ_OfType();
void GScr_LINQ_Sort();
void GScr_LINQ_Average();
void GScr_LINQ_Sum();
void GScr_LINQ_Range();
void GScr_LINQ_Repeat();
void GScr_LINQ_Reverse();
void GScr_LINQ_Concat();
void GScr_LINQ_Chunk();
void GScr_LINQ_Contains();
void GScr_LINQ_IndexOf();
void GScr_LINQ_Remove();
void GScr_LINQ_RemoveAt();

void Scr_StringMin(VariableValueArray array);
void Scr_VectorMin(VariableValueArray array);
void Scr_NumberMin(VariableValueArray array, int flags);
void Scr_StringMax(VariableValueArray array);
void Scr_VectorMax(VariableValueArray array);
void Scr_NumberMax(VariableValueArray array, int flags);
void Scr_StringCast(VariableValueArray array);
void Scr_IntCast(VariableValueArray array);
void Scr_FloatCast(VariableValueArray array);
void Scr_VectorAverage(VariableValueArray array);
void Scr_NumberAverage(VariableValueArray array, int flags);
void Scr_StringSum(VariableValueArray array);
void Scr_VectorSum(VariableValueArray array);
void Scr_NumberSum(VariableValueArray array, int flags);
