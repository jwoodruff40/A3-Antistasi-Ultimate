/**
    Calculates weight (preference - for use in weighted list(s)) of given item based on attributes important to that item type.
	Currently supports weapon item types, but is structured to calculate additional types in the future.

	Author: jwoodruff40

	Uses some concepts (and particularly _impact calculation) from ACE.
	Thanks ACE!
	(https://github.com/acemod/ACE3)

    Params:
        _class - ( String ) - Class of the item to calculate weight for.
		_itemType - ( String ) - Type of the item (e.g. "SniperRifles", "Handguns", "ArmoredVests", etc). Item type determines which calculation to use / which attributes to include in the calculation.

    Returns:
        _arrayWeight - ( Number ) - weight for use in weighted list / selection by selectRandomWeighted.
**/

#include "..\..\script_component.hpp"
FIX_LINE_NUMBERS()

params ["_class", ["_itemType", ""]];

private _config = _class call A3A_fnc_itemConfig;
private _magcfg = getArray (_config >> "Magazines") # 0 call A3A_fnc_itemConfig;
private _ammocfg = getText (_magcfg >> "ammo") call A3A_fnc_itemConfig;
private _firemode = getArray (_config >> "modes") # 0; // primary firemode ("SINGLE", "FULLAUTO", etc)
private _modecfg = [_config >> _firemode, _config] select (_firemode == "this");
private _categories = _class call A3A_fnc_equipmentClassToCategories;

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
private _isDisposable = [0, 20] select ("Disposable" in _categories);

// Total "score" (array weight) of the weapon based on calculated properties
private _arrayWeight = 1; // in case this function is called with an itemType without custom weighting setup or without an item type, just use default weight (but this shouldn't be called unless you're attempting to change this behavior)

switch (_itemType) do {
	// Calculate _arrayWeight based on item attributes above, and scaling them as needed (which attributes and how they're scaled dependent on item type)
	case "Rifles": { _arrayWeight = round ((_accuracy * 10000) + _rof + _magcap + (_impact / 30) - (_weight / 5)) }; // Rifles. Blend of most attributes
	case "SniperRifles" : { _arrayWeight = round ((_accuracy * 50000) + (_effrange / 15) + (_impact / 30) + _rof - (_weight/3)) }; // Favor accuracy and range more. RoF still factored due to generally shorter range / more frenetic AI engagements.
	case "GrenadeLaunchers";
	case "MachineGuns";
	case "SMGs";
	case "Shotguns";
	case "PrimaryWeaponsCatchAll" : { _arrayWeight = round ((_accuracy * 10000) + _rof + _magcap + (_impact / 30) - (_weight / 5)) }; // Primary weapons catchall. Same as Rifles.
	case "RocketLaunchers" : { _arrayWeight = round ((_impact * _caliber / 20) + (_effrange / 4) - (_weight / 2) - _isDisposable) }; // Multiplies impact by caliber (penetration) to favor launchers better against vehicles.
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