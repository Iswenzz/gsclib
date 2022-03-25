#pragma once
#include <cgsc.h>

/**
 * @brief 
 * Get the distance between 2 3D vectors.
 */
float vec_distance(vec3_t a, vec3_t b);

/**
 * @brief 
 * qsort vec3_t comparison function.
 * @param a - Pointer to an vec3_t.
 * @param b - Pointer to an vec3_t.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int vec3_cmp(const void *a, const void *b);

/**
 * @brief 
 * qsort int comparison function.
 * @param a - Pointer to an int.
 * @param b - Pointer to an int.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int int_cmp(const void *a, const void *b);

/**
 * @brief 
 * qsort float comparison function.
 * @param a - Pointer to an float.
 * @param b - Pointer to an float.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int float_cmp(const void *a, const void *b);

/**
 * @brief 
 * qsort C-string comparison function.
 * @param a - Pointer to a char pointer.
 * @param b - Pointer to a char pointer.
 * @return int - strcmp result.
 */
int cstring_cmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable vec3_t comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int gsc_vec3_cmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable int comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int gsc_int_cmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable float comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - returns negative if b > a, and positive if a > b.
 */
int gsc_float_cmp(const void *a, const void *b);

/**
 * @brief 
 * qsort GSC variable string comparison function.
 * @param a - Pointer to a VariableValue.
 * @param b - Pointer to a VariableValue.
 * @return int - strcmp result.
 */
int gsc_cstring_cmp(const void *a, const void *b);
