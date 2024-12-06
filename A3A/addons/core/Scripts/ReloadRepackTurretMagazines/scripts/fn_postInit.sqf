#include "..\..\..\script_component.hpp"

if (!hasInterface) exitWith {};

addUserActionEventHandler ["ReloadMagazine", "Activate", A3A_fnc_reloadTurret];
