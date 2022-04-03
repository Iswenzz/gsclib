#pragma once
#include <cgsc.h>

/**
 * @brief 
 * Print a message to the console output.
 */
void GScr_ComPrintf();

/**
 * @brief 
 * Get the type name of a GSC variable.
 */
void GScr_GetType();

/**
 * @brief 
 * Check the condition and return the 1st value if true or the second value if false.
 */
void GScr_Ternary();

/**
 * @brief 
 * Give a default value if the variable is undefined.
 */
void GScr_IfUndef();
