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


/**
 * @brief Check if a flag is set in the GSC array flag variable.
 * 
 * @param var - GSC array flag variable.
 * @param flag - The flag to test.
 * @return qboolean - The result of the test.
 */
qboolean HasFlag(int var, int flag);

/**
 * @brief Check if the specified flag is the only flag set in the GSC array flag variable.
 * 
 * @param var - GSC array flag variable.
 * @param flag - The flag to test.
 * @return qboolean - The result of the test.
 */
qboolean IsFlag(int var, int flag);
