/*
    Generate the rebel gear array for equipping AIs

Parameters:
    No parameters, returns nothing

Environment:
    Server, scheduled or unscheduled
*/

#include "..\..\script_component.hpp"
#include "\A3\Ui_f\hpp\defineResinclDesign.inc"     // jna_datalist indices
FIX_LINE_NUMBERS()
if (!isServer) exitWith { Error("Server-only function miscalled") };
Info("Started updating A3A_rebelGear");

// Base weight mappings, MIN->0, MAX->1
#define ITEM_MIN 10
#define ITEM_MAX 50

private _fnc_itemArrayWeight = { // heavily inspired by / borrowed from ACE3 Arsenal Weapon Stats
    params ["_class", ["_itemType", ""]];

    private _config = _class call A3A_fnc_itemConfig;
    private _magcfg = getArray (_config >> "Magazines") # 0 call A3A_fnc_itemConfig;
    private _ammocfg = getText (_magcfg >> "ammo") call A3A_fnc_itemConfig;
    private _firemode = getArray (_config >> "modes") # 0; // primary firemode ("SINGLE", "FULLAUTO", etc)
    private _modecfg = [_config >> _firemode, _config] select (_firemode == "this");
    
    private _weight = (_config call A3A_fnc_itemConfigMass); // Mass / Weight
    private _accuracy = getNumber (_modecfg >> "dispersion"); // Dispersion / Accuracy
    private _reloadtime = getNumber (_modecfg >> "reloadTime"); 
    private _rof = [1 / _reloadtime, 0] select (_reloadTime == 0); // Rate of Fire (rounds per second)
    private _magcap = getNumber (_magcfg >> "count"); // Mag Capacity
    private _hit = getNumber ( _ammocfg >> "hit");
    private _basevel = getNumber (_config >> "initSpeed");
    private _magvel = getNumber (_magcfg >> "initSpeed"); 
    private _muzvel = if (_basevel > 0) then { _basevel } else { if (_basevel == 0) then { _magvel } else { abs _basevel * _magvel } };
    private _impact = sqrt (_hit ^ 2 * _muzvel); // impact based on ACE3 concept combining hit / damage and velocity of projectile; modified from ACE3\addons\ACE_ARSENAL\functions\fnc_statBarStatement_impact.sqf
    private _caliber = getNumber (_ammocfg >> "caliber"); // Unintuitively by name, this is a penetration multiplier. More useful for rockets / missiles than bullets.
    private _effrange = 0; // not always reliable (hence not used in most weapons). Iterates through all firemodes, so probably doesn't need to be run for every weapon type.
    if (_firemode == "this") then {
        _effrange = getNumber (_config >> "MidRange") * getNumber (_config >> "MidRangeProbab");
    } else {
        {
            private _range = getNumber (_config >> _x >> "MidRange") * getNumber (_config >> _x >> "MidRangeProbab");
            if (_range > _effrange) then { _effrange = _range };
        } forEach getArray (_config >> "modes");
    };

    // Total "score" (array weight) of the weapon based on calculated properties
    private _arrayWeight = 1; // in case this function is called with an itemType without custom weighting setup or without an item type, just use default weight (but this shouldn't be called unless you're attempting to change this behavior)

    switch (_itemType) do {
        // Calculate _arrayWeight based on item attributes above, and scaling them as needed (which attributes and how they're scaled dependent on item type)
        case "Rifles": { _arrayWeight = round ((_accuracy * 10000) + _rof + _magcap + (_impact / 30) - (_weight / 5)) }; // Rifles. Blend of most attributes
        case "SniperRifles" : { _arrayWeight = round ((_accuracy * 50000) + (_effrange / 15) + (_impact / 30) + (_rof) - (_weight/3)) }; // Favor accuracy and range more. RoF still factored due to generally shorter range / more frenetic AI engagements.
        case "GrenadeLaunchers";
        case "MachineGuns";
        case "SMGs";
        case "Shotguns";
        case "PrimaryWeaponsCatchAll" : { _arrayWeight = round ((_accuracy * 10000) + _rof + _magcap + (_impact / 30) - (_weight / 5)) }; // Primary weapons catchall. Same as Rifles.
        case "RocketLaunchers" : { _arrayWeight = round ((_impact * _caliber / 20) + (_effrange / 4) - (_weight / 2)) }; // Multiplies impact by caliber (penetration) to favor launchers better against vehicles.
        case "MissileLaunchersAT";
        case "MissileLaunchersAA";
        case "SecondaryWeaponsCatchAll" : { _arrayWeight = 1 }; // placeholder catchall for launchers
        case "Handguns" : { _arrayWeight = round (_rof + _magcap + (_impact * 20000) - (_weight * 2.5)) }; // Handguns. Array weight favors weapons with high RoF, Mag capacity, and impact force while heavily discriminating against weight, since it's a backup weapon.
        case "ArmoredVests";
        case "CivilianVests";
        case "ArmoredHeadgear";
        case "Backpacks";
        case "GearCatchAll" : { _arrayWeight = 1 }; // placeholder catchall for gear (vests, helmets, backpacks)
    };
    
    _arrayWeight;
};

private _fnc_addItemNoUnlocks = {
    params ["_array", "_class", "_amount", ["_arrayWeight", 1]];
    if (_amount < 0) exitWith { _array append [_class, _arrayWeight] };
    if (_amount <= ITEM_MIN) exitWith {};
    _array pushBack _class;
    _array pushBack (linearConversion [ITEM_MIN, ITEM_MAX, _amount, 0, 1, true] * _arrayWeight); // multiply weight (preference) by ratio of amount of item to max amount of that item such that items rebels have more of are more likely to be selected
};

private _fnc_addItemUnlocks = {
    params ["_array", "_class", "_amount", ["_arrayWeight", 1]];
    if (_amount < 0) exitWith { _array append [_class, _arrayWeight] };
};

private _fnc_addItem = [_fnc_addItemUnlocks, _fnc_addItemNoUnlocks] select (minWeaps < 0);


// Work with temporary array so that we're not transferring partials
private _rebelGear = createHashMap;

// Primary weapon filtering
private _rifle = [];
private _smg = [];
private _shotgun = [];
private _sniper = [];
private _mg = [];
private _gl = [];

{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    private _itemTypes = [
        ["GrenadeLaunchers", _gl],
        ["Rifles", _rifle],
        ["SniperRifles", _sniper],
        ["MachineGuns", _mg],
        ["SMGs", _smg],
        ["Shotguns", _shotgun]
    ];

    {
        _x params ["_itemType", "_array"];
        _arrayWeight = [_class, _itemType] call _fnc_itemArrayWeight;
        if (_itemType in _categories) then { [_array, _class, _amount, _arrayWeight] call _fnc_addItem };
    } forEach _itemTypes;

} forEach (jna_dataList select IDC_RSCDISPLAYARSENAL_TAB_PRIMARYWEAPON);

_rebelGear set ["Rifles", _rifle];
_rebelGear set ["SMGs", _smg];
_rebelGear set ["Shotguns", _shotgun];
_rebelGear set ["MachineGuns", _mg];
_rebelGear set ["SniperRifles", _sniper];
_rebelGear set ["GrenadeLaunchers", _gl];

// Secondary weapon filtering
private _rlaunchers = [];
private _mlaunchersAT = [];
private _mlaunchersAA = [];
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
/*    if !("Disposable" in _categories) then {
        private _magcount = _class call _fnc_magCount;
        _amount = _amount min (_magcount/2);
    };*/

    if ("RocketLaunchers" in _categories) then { [_rlaunchers, _class, _amount] call _fnc_addItem; continue };
    if ("MissileLaunchers" in _categories) then {
        if ("AA" in _categories) exitWith { [_mlaunchersAA, _class, _amount] call _fnc_addItemNoUnlocks };
        if ("AT" in _categories) exitWith { [_mlaunchersAT, _class, _amount] call _fnc_addItemNoUnlocks };
    };
} forEach (jna_datalist select IDC_RSCDISPLAYARSENAL_TAB_SECONDARYWEAPON);

_rebelGear set ["RocketLaunchers", _rlaunchers];
_rebelGear set ["MissileLaunchersAT", _mlaunchersAT];
_rebelGear set ["MissileLaunchersAA", _mlaunchersAA];

// Vest filtering
private _avests = ["", [1.5,0.5] select (minWeaps < 0)];     // blank entry to phase in armour use gradually
private _uvests = [];
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    private _array = [_uvests, _avests] select ("ArmoredVests" in _categories);
    [_array, _class, _amount] call _fnc_addItem;
} forEach (jna_datalist select IDC_RSCDISPLAYARSENAL_TAB_VEST);

_rebelGear set ["ArmoredVests", _avests];
_rebelGear set ["CivilianVests", _uvests];

// Helmet filtering
private _aheadgear = ["", [1.5,0.5] select (minWeaps < 0)];     // blank entry to phase in armour use gradually
private _uheadgear = [];
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    private _array = [_uheadgear, _aheadgear] select ("ArmoredHeadgear" in _categories);
    [_array, _class, _amount] call _fnc_addItem;
} forEach (jna_datalist select IDC_RSCDISPLAYARSENAL_TAB_HEADGEAR);

_rebelGear set ["ArmoredHeadgear", _aheadgear];
//_rebelGear set ["CosmeticHeadgear", _uheadgear];           // not used, rebels have template-defined basic headgear

// Backpack filtering
private _backpacks = [];
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    if ("BackpacksCargo" in _categories) then { [_backpacks, _class, _amount] call _fnc_addItem };
} forEach (jna_datalist select IDC_RSCDISPLAYARSENAL_TAB_BACKPACK);

_rebelGear set ["BackpacksCargo", _backpacks];

// NVG filtering
private _nvgs = ["", 0.5];          // blank entry for phase-in
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    if !("NVGThermal" in _categories) then { [_nvgs, _class, _amount] call _fnc_addItem };
} forEach (jna_datalist select IDC_RSCDISPLAYARSENAL_TAB_NVGS);

_rebelGear set ["NVGs", _nvgs];

// Unfiltered stuff (just radios atm? could add GPS)
private _radios = [];
{ [_radios, _x#0, _x#1] call _fnc_addItem } forEach (jna_dataList select IDC_RSCDISPLAYARSENAL_TAB_RADIO);
_rebelGear set ["Radios", _radios];

// Misc items. Don't really need weighting but whatever
private _minedetectors = [];
private _toolkits = [];
private _medikits = [];
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    call {
        if ("MineDetectors" in _categories) exitWith { [_minedetectors, _class, _amount] call _fnc_addItem };
        if ("Toolkits" in _categories) exitWith { [_toolkits, _class, _amount] call _fnc_addItem };
        if ("Medikits" in _categories) exitWith { [_medikits, _class, _amount] call _fnc_addItem };
    };
} forEach (jna_dataList select IDC_RSCDISPLAYARSENAL_TAB_CARGOMISC);

_rebelGear set ["MineDetectors", _minedetectors];
_rebelGear set ["Toolkits", _toolkits];
_rebelGear set ["Medikits", _medikits];

// Hand grenades
private _smokes = [];
private _nades = [];
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    call {
        if ("SmokeGrenades" in _categories) exitWith { [_smokes, _class, _amount] call _fnc_addItem };
        if ("Grenades" in _categories) exitWith { [_nades, _class, _amount] call _fnc_addItem };
    };
} forEach (jna_datalist select IDC_RSCDISPLAYARSENAL_TAB_CARGOTHROW);

_rebelGear set ["SmokeGrenades", _smokes];
_rebelGear set ["Grenades", _nades];

// Explosives. Could add mines but don't want them atm.
private _charges = [];
{
    _x params ["_class", "_amount"];
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    if ("ExplosiveCharges" in _categories) then { [_charges, _class, _amount] call _fnc_addItemNoUnlocks };
} forEach (jna_datalist select IDC_RSCDISPLAYARSENAL_TAB_CARGOPUT);

_rebelGear set ["ExplosiveCharges", _charges];

// Optic filtering. No weighting because of weapon compatibilty complexity
private _opticClose = [];
private _opticMid = [];
private _opticLong = [];
private _midCount = 0;
{
    _x params ["_class", "_amount"];
    if (_amount > 0 and {minWeaps > 0 or _amount < ITEM_MIN}) then { continue };
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    call {
        if ("OpticsMid" in _categories) exitWith {                      // most common first
            _opticMid pushBack _class;
            _midCount = [_midCount + _amount, 1e6] select (_amount < 0);
        };
        if ("OpticsClose" in _categories) exitWith { _opticClose pushBack _class };
        if ("OpticsLong" in _categories) exitWith { _opticLong pushBack _class };
    };
} forEach (jna_dataList select IDC_RSCDISPLAYARSENAL_TAB_ITEMOPTIC);

// Mix in some short-range optics if mid-range count is low
if (_midCount < ITEM_MAX*2) then {
    if (_midCount == 0) exitWith { _opticMid = _opticClose };
    private _mixCount = round (count _opticMid * (ITEM_MAX / _midCount));
    if (_mixCount >= count _opticClose) exitWith { _opticMid append _opticClose };

    private _opticClose2 = +_opticClose;
    for "_i" from 1 to _mixCount do {
        private _optic = selectRandom _opticClose2;
        _opticClose2 deleteAt (_opticClose2 find _optic);
        _opticMid pushBack _optic;
    };
};

_rebelGear set ["OpticsClose", _opticClose];
_rebelGear set ["OpticsMid", _opticMid];
_rebelGear set ["OpticsLong", _opticLong];
_rebelGear set ["OpticsAll", _opticClose + _opticMid + _opticLong];     // for launchers

// Light attachments, also no weights because of weapon compat
private _lights = [];
{
    _x params ["_class", "_amount"];
    if (_amount > 0 and {minWeaps > 0 or _amount < ITEM_MIN}) then { continue };
    private _categories = _class call A3A_fnc_equipmentClassToCategories;
    if ("LightAttachments" in _categories) then { _lights pushBack _class };
} forEach (jna_dataList select IDC_RSCDISPLAYARSENAL_TAB_ITEMACC);

_rebelGear set ["LightAttachments", _lights];

// Update everything while unscheduled so that version numbers match
isNil {
    A3A_rebelGearVersion = time;
    _rebelGear set ["Version", A3A_rebelGearVersion];
    A3A_rebelGear = _rebelGear;

    // Clear these two locally
    A3A_rebelOpticsCache = createHashMap;
    A3A_rebelFlashlightsCache = createHashMap;
};
// Only broadcast the version number so that clients & HCs can request as required
publicVariable "A3A_rebelGearVersion";

Info("Finished updating A3A_rebelGear");

/*
// Alternatively just broadcast it
A3A_rebelGear = _rebelGear;
publicVariable "A3A_rebelGear";
*/
