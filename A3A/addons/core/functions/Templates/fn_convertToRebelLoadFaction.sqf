/*
 * File: fn_loadFaction.sqf
 * Author: Spoffy (original), jwoodruff40 (convert to rebel faction)
 * Description:
 *    Loads a faction definition file, converts as necessary to load Occ / Inv as a rebel faction
 * Params:
 *    _filepaths - Single or array of faction definition filepath
 * Returns:
 *    Namespace containing faction information
 * Example Usage:
 */

#include "..\..\script_component.hpp"
params [
	["_filepaths",[],["",[]]]
];

if (_filepaths isEqualType "") then {_filepaths = [_filepaths]};
if (count _filepaths == 0) then {Error("No filepaths provided.")};

private _dataStore = createHashMap;

private _fnc_saveToTemplate = {
	params ["_name", "_data"];

	private _enemyConfigIgnore = [
		"vehiclesGunBoats",
		"vehiclesPlanesLargeCAS",
		"vehiclesPlanesLargeAA",
		"vehiclesPlanesGunship",
		"vehiclesMilitiaTrucks",
		"vehiclesMilitiaLightArmed",
		"vehiclesMilitiaCars",
		"vehiclesCargoTrucks",
		"vehiclesAmmoTrucks",
		"vehiclesRepairTrucks",
		"vehiclesFuelTrucks",
		"vehiclesMedical",
		"vehiclesTanks",
		"vehiclesHelisTransport",
		"vehiclesPolice",
		"vehiclesHelisLightAttack",
		"staticHowitzers",
		"vehicleRadar",
		"vehicleSam",
		"vehiclesPlanesCAS",
		"vehiclesPlanesAA",
		"vehiclesArtillery",
		"vehiclesLightAPCs",
		"vehiclesAPCs",
		"vehiclesIFVs",
		"vehiclesLightTanks",
		"vehiclesAirborne",
		"vehiclesMilitiaAPCs"
	];

	if (_name in _enemyConfigIgnore) exitWith {};

	private _enemyToRebelConfigMap = createHashmapFromArray [
	["mortarMagazineHE", "staticMortarMagHE"],
	["mortarMagazineSmoke", "staticMortarMagSmoke"],
	["mortarMagazineFlare", "staticMortarMagFlare"],
	["ATMines", "minesAT"],
	["APMines", "minesAPERS"],
	["lightExplosives", "breachingExplosivesAPC"],
	["heavyExplosives", "breachingExplosivesTank"],
	["vehiclesTransportBoats", "vehiclesBoat"]
	];

	if (_name in keys _enemyToRebelConfigMap) then {
		_dataStore set [_enemyToRebelConfigMap get _name, _data]
	} else {
		if (_name == "attributesVehicles") then {
			private _attributesVehicles = [];
			{
				private _cost = (_x select 1) select 1;
				_attributesVehicles pushBack [_x select 0, ["rebCost", _cost]];
			} forEach (_data);
			_data = _attributesVehicles;
		};

		_dataStore set [_name, _data]
	};
};

private _fnc_getFromTemplate = {
	params ["_name"];

	_dataStore get _name;
};

//Keep track of loadout namespaces so we can delete them when we're done.
private _loadoutNamespaces = [];
private _fnc_createLoadoutData = {
	private _namespace = createHashMap;
	_loadoutNamespaces pushBack _namespace;
	_namespace
};

private _fnc_copyLoadoutData = {
	params ["_sourceNamespace"];
    + _sourceNamespace //hashmaps deepcopy with +
};

private _allLoadouts = createHashMap;
_dataStore set ["loadouts", _allLoadouts];

private _fnc_saveUnitToTemplate = {
	params ["_typeName", "_loadouts", ["_traits", []], ["_unitProperties", []]];
	private _unitDefinition = [_loadouts, _traits, _unitProperties];
	_allLoadouts set [_typeName, _unitDefinition];
};

private _fnc_generateAndSaveUnitToTemplate = {
	params ["_name", "_template", "_loadoutData", ["_traits", []], ["_unitProperties", []]];
	private _loadouts = [];
	for "_i" from 1 to 5 do {
		_loadouts pushBack ([_template, _loadoutData] call A3A_fnc_loadout_builder);
	};
	[_name, _loadouts, _traits, _unitProperties] call _fnc_saveUnitToTemplate;
};

private _fnc_generateAndSaveUnitsToTemplate = {
	// * Overwrite this function because we don't want to pointlessly generate a bunch of loadouts
	// * Instead, use the call to this function to populate faction equipment into rebel initial equipment (weapons, mostly)
	params ["_prefix", "_unitTemplates", "_loadoutData"];
	private _ire = _dataStore getOrDefault ["initialRebelEquipment", [], true];
	// * We only want to run this once, so we only get the equipment from the highest tier (e.g. if we populate IRE from sfLoadoutData, we don't want to add equipment from eliteLoadoutData, etc)
	if (_ire isNotEqualTo []) exitWith {};
	{
		private _items = (flatten _y) select {_x isEqualType "" && {_x != ""}}; // remove empties
		_items = _items arrayIntersect _items; // remove duplicates

		if (_x == "uniforms") then { _dataStore set ["uniforms", _items] };
		private _unlimitedItemTypes = [
			"antiInfantryGrenades",
			"smokeGrenades",
			//"rifles",
			"sniperRifles", // * petros and rebel recruits need at least *some* unlimited weapon at game start. SMGs / shotguns not defined in all templates, and they don't use handguns (currently)
			"sidearms",
			"maps",
			"watches",
			"compasses",
			"binoculars",
			"items_medical_basic",
			"items_medical_standard",
			"items_medical_medic",
			"items_miscEssentials",
			"items_engineer_extras",
			"items_marksman_extras",
			"uniforms",
			"traitorUniforms",
			"officerUniforms",
			"glasses",
			"goggles"
		];

		if (_x in _unlimitedItemTypes) then { _ire append _items; continue };
		
		
		{
			private _categories = _x call A3A_fnc_equipmentClassToCategories;

			switch true do {
				case ("Weapons" in _categories): { _ire pushback [_x, [3 min minWeaps, 5] select (minWeaps < 0)] };
				case ("Grenades" in _categories);
				case ("MagSmokeShell" in _categories);
				case ("Explosives" in _categories);
				case ("MagMissile" in _categories);
				case ("MagRocket" in _categories): { _ire pushback [_x, [3 min minWeaps, 5] select (minWeaps < 0)] };
				case ("Magazines" in _categories): {
					private _magCap = getNumber (configFile >> "CfgMagazines" >> _x >> "count");
					_ire pushback [_x, [20*_magCap min minWeaps*_magCap, 25*_magCap] select (minWeaps < 0)];
				};
				case ("Vests" in _categories && {!("ArmoredVests" in _categories)});
				case ("Backpacks" in _categories && {!("BackpacksCargo" in _categories)}): { _ire pushback _x };
				default { _ire pushBack [_x, [3 min minWeaps, 5] select (minWeaps < 0)] };
			};
		} forEach _items;
	} forEach _loadoutData;
};

private _fnc_generateAndSaveRebelUnitsToTemplate = {
	params ["_prefix", "_unitTemplates", "_loadoutData"];
	{
		_x params ["_name", "_template", ["_traits", []], ["_unitProperties", []]];
		private _finalName = format ["%1_%2", _prefix, _name];
		[_finalName, _template, _loadoutData, _traits, _unitProperties] call _fnc_generateAndSaveUnitToTemplate;
	} forEach _unitTemplates;
};

private _fnc_saveNames = {
    params ["_names"];
    private _nameConfig = configfile >> "CfgWorlds" >> "GenericNames" >> _names;
    private _firstNames = configProperties [_nameConfig >> "FirstNames"] apply { getText(_x) };
    ["firstNames", _firstNames] call _fnc_saveToTemplate;
    private _lastNames = configProperties [_nameConfig >> "LastNames"] apply { getText(_x) };
    ["lastNames", _lastNames] call _fnc_saveToTemplate;
};

{
	call compile preprocessFileLineNumbers _x;
} forEach _filepaths;

// * overrides
_dataStore set ["flagMarkerType", "flag_FIA"];

{ _dataStore set [_x, []]; } forEach ["vehiclesCivHeli", "vehiclesCivTruck", "vehiclesCivCar", "vehiclesCivBoat"];

////////////////////////
//  Rebel Unit Types  //
///////////////////////.

private _rebelSquadLeaderTemplate = {
    ["uniforms"] call _fnc_setUniform;
    [selectRandomWeighted [[], 1.25, "glasses", 1, "goggles", 0.75, "facemask", 1, "balaclavas", 1, "argoFacemask", 1 , "facewearWS", 0.75, "facewearContact", 0.3, "facewearLawsOfWar", 0.5, "facewearGM", 0.3, "facewearCLSA", 0.2,"facewearSOG", 0.3,"facewearSPE", 0.2]] call _fnc_setFacewear;

    ["items_medical_standard"] call _fnc_addItemSet;
    ["items_miscEssentials"] call _fnc_addItemSet;

    ["maps"] call _fnc_addMap;
    ["watches"] call _fnc_addWatch;
    ["compasses"] call _fnc_addCompass;
    ["binoculars"] call _fnc_addBinoculars;
};

private _rebelRiflemanTemplate = {
    ["uniforms"] call _fnc_setUniform;
    [selectRandomWeighted [[], 1.25, "glasses", 1, "goggles", 0.75, "facemask", 1, "balaclavas", 1, "argoFacemask", 1 , "facewearWS", 0.75, "facewearContact", 0.3, "facewearLawsOfWar", 0.5, "facewearGM", 0.3, "facewearCLSA", 0.2, "facewearSOG", 0.3,"facewearSPE", 0.2]] call _fnc_setFacewear;
    
    ["items_medical_standard"] call _fnc_addItemSet;
    ["items_miscEssentials"] call _fnc_addItemSet;

    ["maps"] call _fnc_addMap;
    ["watches"] call _fnc_addWatch;
    ["compasses"] call _fnc_addCompass;
};

private _prefix = "militia";
private _unitTypes = [
    ["Petros", _rebelSquadLeaderTemplate],
    ["SquadLeader", _rebelSquadLeaderTemplate],
    ["Rifleman", _rebelRiflemanTemplate],
    ["staticCrew", _rebelRiflemanTemplate],
    ["Medic", _rebelRiflemanTemplate, [["medic", true]]],
    ["Engineer", _rebelRiflemanTemplate, [["engineer", true]]],
    ["ExplosivesExpert", _rebelRiflemanTemplate, [["explosiveSpecialist", true]]],
    ["Grenadier", _rebelRiflemanTemplate],
    ["LAT", _rebelRiflemanTemplate],
    ["AT", _rebelRiflemanTemplate],
    ["AA", _rebelRiflemanTemplate],
    ["MachineGunner", _rebelRiflemanTemplate],
    ["Marksman", _rebelRiflemanTemplate],
    ["Sniper", _rebelRiflemanTemplate],
    ["Unarmed", _rebelRiflemanTemplate]
];

[_prefix, _unitTypes, _dataStore] call _fnc_generateAndSaveRebelUnitsToTemplate;


_dataStore
