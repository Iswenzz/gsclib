#pragma once
#include <cgsc.h>

/// <summary>
/// Get the smallest value from an array of int/float/string/vector.
/// </summary>
void GScr_LINQ_Min();

/// <summary>
/// Get the biggest value from an array of int/float/string/vector.
/// </summary>
void GScr_LINQ_Max();

/// <summary>
/// Reconstruct an array with all items casted to a specific type.
/// Available types are : int, float, string.
/// </summary>
void GScr_LINQ_Cast();

/// <summary>
/// Reconstruct the array with only the specified type.
/// Available types are : int, float, string.
/// </summary>
void GScr_LINQ_OfType();

/// <summary>
/// Sort all items from an array of int/float/string/vector.
/// </summary>
void GScr_LINQ_Sort();

/// <summary>
/// Get the average value from an array of int/float/vector.
/// </summary>
void GScr_LINQ_Average();

/// <summary>
/// Adds all values from an array of int/float/vector/string.
/// </summary>
void GScr_LINQ_Sum();

/// <summary>
/// Reconstruct the array with a specified range.
/// </summary>
void GScr_LINQ_Range();

/// <summary>
/// Repeat all values in an array.
/// </summary>
void GScr_LINQ_Repeat();

/// <summary>
/// Reverse the array.
/// </summary>
void GScr_LINQ_Reverse();

/// <summary>
/// Concat an array with another array.
/// </summary>
void GScr_LINQ_Concat();

/// <summary>
/// Split an array into multiple chunks.
/// </summary>
void GScr_LINQ_Chunk();

/// <summary>
/// Check and array contains an element.
/// </summary>
void GScr_LINQ_Contains();

/// <summary>
/// Get the index of an element.
/// </summary>
void GScr_LINQ_IndexOf();

/// <summary>
/// Remove an element from the array.
/// </summary>
void GScr_LINQ_Remove();

/// <summary>
/// Remove and element at a specific index in the array.
/// </summary>
void GScr_LINQ_RemoveAt();

/// <summary>
/// Get the min string in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_StringMin(VariableValueArray array);

/// <summary>
/// Get the min vector in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_VectorMin(VariableValueArray array);

/// <summary>
/// Get the min number in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
/// <param name="flags">The array type flags.</param>
void Scr_NumberMin(VariableValueArray array, int flags);

/// <summary>
/// Get the max string in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_StringMax(VariableValueArray array);

/// <summary>
/// Get the max vector in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_VectorMax(VariableValueArray array);

/// <summary>
/// Get the max number in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
/// <param name="flags">The array type flags.</param>
void Scr_NumberMax(VariableValueArray array, int flags);

/// <summary>
/// Cast all variables to string.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_StringCast(VariableValueArray array);

/// <summary>
/// Cast all variables to int.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_IntCast(VariableValueArray array);

/// <summary>
/// Cast all variables to float.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_FloatCast(VariableValueArray array);

/// <summary>
/// Get the average vector in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_VectorAverage(VariableValueArray array);

/// <summary>
/// Get the average number in a GSC array.
/// </summary>
/// <param name="array">The variable array.</param>
/// <param name="flags">The array type flags.</param>
void Scr_NumberAverage(VariableValueArray array, int flags);

/// <summary>
/// Sum all strings.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_StringSum(VariableValueArray array);

/// <summary>
/// Sum all vectors.
/// </summary>
/// <param name="array">The variable array.</param>
void Scr_VectorSum(VariableValueArray array);

/// <summary>
/// Sum all numbers.
/// </summary>
/// <param name="array">The variable array.</param>
/// <param name="flags">The array type flags.</param>
void Scr_NumberSum(VariableValueArray array, int flags);
