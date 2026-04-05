//includes commonly included files to clean up includes in other files
//Line number fix
#define FIX_LINE_NUMBERS2(sharp) sharp##line __LINE__ __FILE__
#define FIX_LINE_NUMBERS() FIX_LINE_NUMBERS2(#)

#include "LogMacros.inc"

//Template macros
#define Faction(SIDE) (switch SIDE do {case west:{A3A_faction_occ}; case east:{A3A_faction_inv}; case resistance:{A3A_faction_reb}; case civilian:{A3A_faction_civ}; case opfor:{A3A_faction_riv}; default {Error_1("Bad side passed passed to Faction(side), Side: %1", SIDE); createHashMap};})
#define FactionGet(FAC, VAR) (A3A_faction_##FAC get VAR)
#define FactionGetOrDefault(FAC, VAR, DEF) (A3A_faction_##FAC getOrDefault [VAR, DEF])
#define FactionGetTiered(FAC, VAR) ([A3A_faction_##FAC get VAR] call SCRT_fnc_unit_getTiered)
#define FactionGetAll(FAC, VAR) (private _array = flatten (A3A_faction_##FAC get VAR); _array arrayIntersect _array)
#define GetTiered(FACVAR, VAR) ([FACVAR get VAR] call SCRT_fnc_unit_getTiered)

/// Feature Toggles ///
// Force new experimental UI.
// #define UseDoomGUI
// Enable completed sections of experimental UI.
#define UseDoomGUIPreview
