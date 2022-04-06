#pragma once
#include <cgsc.h>

/**
 * @brief 
 * Get the distance between 2 3D vectors.
 */
float VectorDistance(vec3_t a, vec3_t b);

/**
 * @brief 
 * qsort vec3_t comparison function.
 * @param a - Pointer to an vec3_t.
 * @param b - Pointer to an vec3_t.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int VectorCmp(const void *a, const void *b);

/**
 * @brief 
 * qsort int comparison function.
 * @param a - Pointer to an int.
 * @param b - Pointer to an int.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int IntCmp(const void *a, const void *b);

/**
 * @brief 
 * qsort float comparison function.
 * @param a - Pointer to an float.
 * @param b - Pointer to an float.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int FloatCmp(const void *a, const void *b);

/**
 * @brief 
 * qsort C-string comparison function.
 * @param a - Pointer to a char pointer.
 * @param b - Pointer to a char pointer.
 * @return int - strcmp result.
 */
int StringCmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable vec3_t comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int Scr_VectorCmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable int comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int Scr_IntCmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable float comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int Scr_FloatCmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable string comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - strcmp result.
 */
int Scr_StringCmp(const void *a, const void *b);
