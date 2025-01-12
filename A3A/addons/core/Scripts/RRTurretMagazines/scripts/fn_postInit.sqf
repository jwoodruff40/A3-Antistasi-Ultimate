#include "..\..\..\script_component.hpp"

if (!hasInterface) exitWith {};

if !(RRTurretMagazines) exitwith {};

addUserActionEventHandler ["ReloadMagazine", "Activate", A3A_fnc_reloadTurret];
