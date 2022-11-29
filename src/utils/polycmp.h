#pragma once
#include <CGSC/cgsc.h>

/// <summary>
/// Get the distance between 2 3D vectors.
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
float VectorDistance(vec3_t a, vec3_t b);

/// <summary>
/// Sort vec3_t comparison function.
/// </summary>
/// <param name="a">Pointer to an vec3_t.</param>
/// <param name="b">Pointer to an vec3_t.</param>
/// <returns>Negative if b > a, and positive if a > b.</returns>
int VectorCmp(const void *a, const void *b);

/// <summary>
/// Sort int comparison function.
/// </summary>
/// <param name="a">Pointer to an int.</param>
/// <param name="b">Pointer to an int.</param>
/// <returns>Negative if b > a, and positive if a > b.</returns>
int IntCmp(const void *a, const void *b);

/// <summary>
/// Sort float comparison function.
/// </summary>
/// <param name="a">Pointer to an float.</param>
/// <param name="b">Pointer to an float.</param>
/// <returns>Negative if b > a, and positive if a > b.</returns>
int FloatCmp(const void *a, const void *b);

/// <summary>
/// Sort string comparison function.
/// </summary>
/// <param name="a">Pointer to a string.</param>
/// <param name="b">Pointer to a string.</param>
/// <returns>strcmp result.</returns>
int StringCmp(const void *a, const void *b);

/// <summary>
/// Sort vec3_t comparison function.
/// </summary>
/// <param name="a">Pointer to a VariableValue.</param>
/// <param name="b">Pointer to a VariableValue.</param>
/// <returns>Negative if b > a, and positive if a > b.</returns>
int Scr_VectorCmp(const void *a, const void *b);

/// <summary>
/// Sort int comparison function.
/// </summary>
/// <param name="a">Pointer to a VariableValue.</param>
/// <param name="b">Pointer to a VariableValue.</param>
/// <returns>Negative if b > a, and positive if a > b.</returns>
int Scr_IntCmp(const void *a, const void *b);

/// <summary>
/// Sort float comparison function.
/// </summary>
/// <param name="a">Pointer to a VariableValue.</param>
/// <param name="b">Pointer to a VariableValue.</param>
/// <returns>Negative if b > a, and positive if a > b.</returns>
int Scr_FloatCmp(const void *a, const void *b);

/// <summary>
/// Sort string comparison function.
/// </summary>
/// <param name="a">Pointer to a VariableValue.</param>
/// <param name="b">Pointer to a VariableValue.</param>
/// <returns>strcmp result.</returns>
int Scr_StringCmp(const void *a, const void *b);
