/*
    Fully equips a rebel infantry unit based on their class and unlocked gear

Parameters:
    0. <OBJECT> Unit to equip
    1. <NUMBER> Recruit type: 0 recruit, 1 HC squad, 2 garrison. Doesn't currently have any effect

Returns:
    Nothing

Environment:
    Scheduled, any machine
*/

/*
loadout = [[primary], [secondary], [handgun], [uniform], [vest], [backpack], "headgear", "facewear", [binoculars], [assigned items]]
assigned items = [map, gps/uav term, radio, compass, watch, nvg]
*/

#include "..\..\script_component.hpp"
FIX_LINE_NUMBERS()

params ["_unit", "_recruitType", ["_forceClass", ""]];

call A3A_fnc_fetchRebelGear;        // Send current version of rebelGear from server if we're out of date

// TODO: add types unitAA and unitAT(name?) when UI is ready
private _unitType = if (_forceClass != "") then {_forceClass} else {_unit getVariable "unitType"};
private _customLoadout = rebelLoadouts get _unitType;

private _fnc_addSecondary = {
    params ["_unit"];

    switch true do {
        case (_unitType isEqualTo FactionGet(reb,"unitRifle") && {random 20 < tierWar});
        case (_unitType isEqualTo FactionGet(reb,"unitLAT"));
        case (_unitType isEqualTo FactionGet(reb,"unitAT"));
        case (_unitType isEqualTo FactionGet(reb,"unitAA")): {
            private _rLaunchers = A3A_rebelGear get "RocketLaunchers";
            private _dLaunchers = [];
            private _mLaunchersAT = A3A_rebelGear get "MissileLaunchersAT";
            private _mLaunchersAA = A3A_rebelGear get "MissileLaunchersAA";

            {
                if ("Disposable" in (_x call A3A_fnc_equipmentClassToCategories)) then { _dLaunchers append [_x, _rlaunchers select (_rlaunchers find _x) + 1 ] };
            } forEach (_rlaunchers select {typeName _x == "STRING"});

            private _launcherPool = createHashMapFromArray [
                [FactionGet(reb,"unitRifle"), _dLaunchers],
                [FactionGet(reb,"unitLAT"), _rLaunchers],
                [FactionGet(reb,"unitAT"), _mLaunchersAT],
                [FactionGet(reb,"unitAA"), _mLaunchersAA]
            ];
            
            private _weapon = selectRandomWeighted (_launcherPool get _unitType);

            _unit addWeapon _weapon;
            //private _magazine = (compatibleMagazines _weapon) arrayIntersect (jna_dataList select IDC_RSCDISPLAYARSENAL_TAB_CARGOMAGALL) select 0;
            private _magazine = compatibleMagazines _weapon select 0;
            _unit addSecondaryWeaponItem _magazine;

            if ("Disposable" in (_weapon call A3A_fnc_equipmentClassToCategories)) exitWith {};
            private _magWeight = 20 max getNumber (configFile / "CfgMagazines" / _magazine / "mass");
            _unit addMagazines [_magazine, round (random 0.5 + 100 / _magWeight)];

            private _compatOptics = A3A_rebelOpticsCache get _weapon;
            if (isNil "_compatOptics") then {
                private _compatItems = compatibleItems _weapon; // cached, should be fast
                _compatOptics = _compatItems arrayIntersect (A3A_rebelGear get "OpticsAll");
                A3A_rebelOpticsCache set [_weapon, _compatOptics];
            };
            if (_compatOptics isNotEqualTo []) then { _unit addSecondaryWeaponItem (selectRandom _compatOptics) };
        };
    };    
};

private _fnc_addCharges = {
    params ["_unit", "_totalWeight"];

    private _charges = A3A_rebelGear get "ExplosiveCharges";
    if (_charges isEqualTo []) exitWith {};

    private _weight = 0;
    while { _weight < _totalWeight } do {
        private _charge = selectRandomWeighted _charges;
        _weight = _weight + getNumber (configFile / "CfgMagazines" / _charge / "mass");
        _unit addItemToBackpack _charge;
    };
};

private _fnc_addRadio = {
    params ["_unit"];
    
    private _radio = selectRandomWeighted (A3A_rebelGear get "Radios");
    if (!isNil "_radio") then {_unit linkItem _radio};
};

private _fnc_addFacewear = {
    params ["_unit"];

    private _goggles = goggles _unit;
    if (goggles _unit != _goggles && {randomizeRebelLoadoutUniforms}) then {
        removeGoggles _unit;
        _unit addGoggles _goggles;
    };
};

private _fnc_addHeadgear = {
    params ["_unit"];
    
    private _helmet = selectRandomWeighted (A3A_rebelGear get "ArmoredHeadgear");
    if (_helmet == "") then { _helmet = selectRandom (A3A_faction_reb get "headgear") };
    _unit addHeadgear _helmet;
};

private _fnc_addVest = {
    params ["_unit"];

    private _vest = selectRandomWeighted (A3A_rebelGear get "ArmoredVests");
    if (_vest == "") then { _vest = selectRandomWeighted (A3A_rebelGear get "CivilianVests") };
    _unit addVest _vest;
};

private _fnc_addBackpack = {
    params ["_unit"];

    private _backpack = selectRandomWeighted (A3A_rebelGear get "BackpacksCargo");
    if !(isNil "_backpack") then { _unit addBackpack _backpack };
};

private _fnc_addGrenades = {
    params ["_unit", ["_gType", ""], ["_gAmount", 1]];

    private _types = [[_gType], ["SmokeGrenades", "Grenades"]] select (isNil _gType);

    {
        private _grenades = A3A_rebelGear get _x;
        if (_grenades isNotEqualTo []) then { _unit addMagazines [selectRandomWeighted _grenades, _gAmount] }
    } forEach _types;
};

private _fnc_addPrimary = {
    params ["_unit"];

    switch (true) do {
        case (_unitType isEqualTo FactionGet(reb,"unitSniper")): {
            [_unit, "SniperRifles", 50] call A3A_fnc_randomRifle;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitMG")): {
            [_unit, "MachineGuns", 150] call A3A_fnc_randomRifle;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitGL")): {
            [_unit, "GrenadeLaunchers", 50] call A3A_fnc_randomRifle;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitLAT"));
        case (_unitType isEqualTo FactionGet(reb,"unitAT"));
        case (_unitType isEqualTo FactionGet(reb,"unitAA"));
        case (_unitType isEqualTo FactionGet(reb,"unitExp")): {
            [_unit, "Rifles", 40] call A3A_fnc_randomRifle;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitEng"));
        case (_unitType isEqualTo FactionGet(reb,"unitSL"));
        case (_unitType isEqualTo FactionGet(reb,"unitCrew")): {
            [_unit, "Rifles", 50] call A3A_fnc_randomRifle;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitRifle")): {
            [_unit, "Rifles", 70] call A3A_fnc_randomRifle;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitMedic")): {
            [_unit, "SMGs", 40] call A3A_fnc_randomRifle;
        };
        default {
            [_unit, "SMGs", 50] call A3A_fnc_randomRifle;
            Error_1("Unknown unit class: %1", _unitType);
        };
    };
};

private _fnc_addClassEquip = {
    params ["_unit"];

    switch (true) do {
        case (_unitType isEqualTo FactionGet(reb,"unitRifle")): {
            [_unit, "Grenades", 2] call _fnc_addGrenades;
            [_unit, "SmokeGrenades", 1] call _fnc_addGrenades;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitExp")): {
            _unit enableAIFeature ["MINEDETECTION", true]; //This should prevent them from Stepping on the Mines as an "Expert" (It helps, they still step on them)

            private _mineDetector = selectRandomWeighted (A3A_rebelGear get "MineDetectors");
            if !(isNil "_mineDetector") then { _unit addItem _mineDetector };

            private _toolkit = selectRandomWeighted (A3A_rebelGear get "Toolkits");
            if !(isNil "_toolkit") then { _unit addItem _toolkit };

            [_unit, 50] call _fnc_addCharges;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitEng")): {
            private _toolkit = selectRandomWeighted (A3A_rebelGear get "Toolkits");
            if !(isNil "_toolkit") then { _unit addItem _toolkit };

            [_unit, 50] call _fnc_addCharges;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitMedic")): {
            [_unit, "SmokeGrenades", 2] call _fnc_addGrenades;

            // not-so-temporary hack
            private _medItems = [];
            {
                for "_i" from 1 to (_x#1) do { _medItems pushBack (_x#0) };
            } forEach (["MEDIC",independent] call A3A_fnc_itemset_medicalSupplies);
            {
                _medItems deleteAt (_medItems find _x);
            } forEach items _unit;
            {
                _unit addItemToBackpack _x;
            } forEach _medItems;
        };
        case (_unitType isEqualTo FactionGet(reb,"unitSL")): {
            [_unit, "SmokeGrenades", 2] call _fnc_addGrenades;
        };
        default {
            Error_1("Unknown unit class: %1", _unitType);
        };
    };
};

private _fnc_addNightEquip = {
    params ["_unit"];

    private _nvg = selectRandomWeighted (A3A_rebelGear get "NVGs");
    if (_nvg != "") then { _unit linkItem _nvg }
    else {
        private _weapon = primaryWeapon _unit;
        private _compatLights = A3A_rebelFlashlightsCache get _weapon;
        if (isNil "_compatLights") then {
            private _compatItems = compatibleItems _weapon; // cached, should be fast
            _compatLights = _compatItems arrayIntersect (A3A_rebelGear get "LightAttachments");
            A3A_rebelFlashlightsCache set [_weapon, _compatLights];
        };
        if (_compatLights isNotEqualTo []) then {
            private _flashlight = selectRandom _compatLights;
            _unit addPrimaryWeaponItem _flashlight;		// should be used automatically by AI as necessary
        };
    };
};

if (!isNil "_customLoadout") then {
    // * remove invalid loadout entries before applying the loadout to the unit
    private _tempLoadout = _customLoadout;
    if ("petros_knows_best" in flatten _tempLoadout) then {
        {
            if (_x isEqualTo "petros_knows_best") then {_tempLoadout set [_forEachIndex, ""]};
        } forEach _tempLoadout;
    };
    _unit setUnitLoadout _tempLoadout;
    
    private _addToLoadout = [
        "_unit call _fnc_addPrimary;",
        "_unit call _fnc_addSecondary;",
        "// handguns", // * not implemented
        "_unit forceAddUniform (selectRandom (A3A_faction_reb get 'uniforms')); {_unit addItemToUniform _x} forEach (uniformItems _unit);",
        "_unit call _fnc_addVest; {_unit addItemToVest _x} forEach (vestItems _unit);",
        "_unit call _fnc_addBackpack; {_unit addItemToBackpack _x} forEach (backpackItems _unit);",
        "_unit call _fnc_addHeadgear;",
        "_unit call _fnc_addFacewear;"
    ];

    {
        if (_x select 0 == "petros_knows_best") then { call compile preprocessFileLineNumbers (_addToLoadout select _forEachIndex); };
    } forEach (_customLoadout select [0,6]);

    {
        if (_x == "petros_knows_best") then { call compile preprocessFileLineNumbers (_addToLoadout select _forEachIndex) };
    } forEach (_customLoadout select [6,2]);

    _unit call _fnc_addClassEquip;
    _unit call _fnc_addNightEquip;
    _unit linkItem (selectRandom (A3A_faction_reb get "compasses"));
	_unit linkItem (selectRandom (A3A_faction_reb get "maps"));
	_unit linkItem (selectRandom (A3A_faction_reb get "watches"));
	if (haveRadio) then {_unit linkItem (selectRandom (A3A_faction_reb get "radios"))};
} else {
    _unit call _fnc_addPrimary;
    _unit call _fnc_addSecondary;
    _unit call _fnc_addVest;
    _unit call _fnc_addBackpack;
    _unit call _fnc_addHeadgear;
    _unit call _fnc_addRadio; 
    _unit call _fnc_addGrenades;
    _unit call _fnc_addClassEquip;
    _unit call _fnc_addNightEquip; 
};

// remove backpack if empty, otherwise squad troops will throw it on the ground
if (backpackItems _unit isEqualTo []) then { removeBackpack _unit };

Verbose_3("Class %1, type %2, loadout %3", _unitType, _recruitType, str (getUnitLoadout _unit));
