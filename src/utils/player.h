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

/// <summary>
/// Get the player's movement flags.
/// </summary>
void GScr_PmFlags(scr_entref_t num);

/// <summary>
/// Set the player's movement flags.
/// </summary>
void GScr_SetPmFlags(scr_entref_t num);

/// <summary>
/// Get the player's movement time.
/// </summary>
void GScr_PmTime(scr_entref_t num);

/// <summary>
/// Set the player's movement time.
/// </summary>
void GScr_SetPmTime(scr_entref_t num);

/// <summary>
/// Get the player's movement type.
/// </summary>
void GScr_PmType(scr_entref_t num);

/// <summary>
/// Get the player's weapon flags.
/// </summary>
void GScr_WeaponFlags(scr_entref_t num);
