#pragma once
#include <cgsc.h>

/// <summary>
/// Get a client IP.
/// </summary>
/// <param name="ent">The client number.</param>
void GScr_GetIP(scr_entref_t num);

/// <summary>
/// Get the player's right move state.
/// </summary>
void GScr_GetRightMove(scr_entref_t num);

/// <summary>
/// Get the player's forward move state.
/// </summary>
void GScr_GetForwardMove(scr_entref_t num);
