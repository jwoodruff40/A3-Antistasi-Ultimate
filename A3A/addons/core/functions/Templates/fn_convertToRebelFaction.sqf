/*

 * File: fn_convertToRebelFaction.sqf
 * Author: jwoodruff40 | Creep'nCrunch
 * Description:
 *    Takes occ / inv faction hashmap as input, extracts and converts keys / values into a rebel faction hashmap.
 * Params:
 *    _faction - Faction hashmap
 * Returns:
 *    Hashmap containing faction information
 * Example Usage:
 * _rebFaction = _milFaction call A3A_fnc_convertToRebelFaction;
 */
#include "..\..\script_component.hpp"
FIX_LINE_NUMBERS()
params ["_faction"];

private _convFaction = createHashMap;

_convFaction set ["flagMarkerType", "flag_FIA", true];

/*
private _initialRebelEquipment = [
	"hgun_Pistol_heavy_02_F",
	"hgun_PDW2000_F",
	"30Rnd_9x21_Mag", "30Rnd_9x21_Red_Mag",
	"6Rnd_45ACP_Cylinder","MiniGrenade","SmokeShell",
	["IEDUrbanSmall_Remote_Mag", 10], ["IEDLandSmall_Remote_Mag", 10], ["IEDUrbanBig_Remote_Mag", 3], ["IEDLandBig_Remote_Mag", 3],
	"B_FieldPack_oli","B_FieldPack_blk","B_FieldPack_khk",
	"V_BandollierB_blk","V_BandollierB_cbr","V_BandollierB_rgr","V_BandollierB_khk","V_BandollierB_oli","V_Rangemaster_belt",
	"Binocular",
	"acc_flashlight","acc_flashlight_smg_01","acc_flashlight_pistol",
	"B_FieldPack_blk","B_AssaultPack_blk",
	["launch_RPG32_F", 2], ["RPG32_F", 6]
];
*/

private _initialRebelEquipment = [];
private _rebUniforms = [];
private _headgear = [];

if (A3A_hasTFAR) then {_initialRebelEquipment append ["tf_microdagr","tf_anprc154"]};
if (A3A_hasTFAR && startWithLongRangeRadio) then {_initialRebelEquipment append ["tf_anprc155","tf_anprc155_coyote"]};
if (A3A_hasTFARBeta) then {_initialRebelEquipment append ["TFAR_microdagr","TFAR_anprc154"]};
if (A3A_hasTFARBeta && startWithLongRangeRadio) then {_initialRebelEquipment append ["TFAR_anprc155","TFAR_anprc155_coyote"]};
_initialRebelEquipment append ["Chemlight_blue","Chemlight_green","Chemlight_red","Chemlight_yellow"];
//_convFaction set ["initialRebelEquipment", _initialRebelEquipment, true];


// * convert items with different key names in enemy factions vs rebel factions
private _enemyToRebelConfigMap = createHashmapFromArray [
	["mortarMagazineHE", "staticMortarMagHE"],
	["mortarMagazineSmoke", "staticMortarMagSmoke"],
	["mortarMagazineFlare", "staticMortarMagFlare"],
	["ATMines", "minesAT"],
	["APMines", "minesAPERS"],
	["lightExplosives", "breachingExplosivesAPC"],
	["heavyExplosives", "breachingExplosivesTank"]
];
{ _convFaction set [_y, _faction get _x, true]; } forEach _enemyToRebelConfigMap;


// * copy items with same key name as is
private _sharedConfig = [
	// information
	"name",
	"flag",
	"flagTexture",

	// vehicles
	"vehiclesBoat",
	"vehiclesBasic",
	"vehiclesPlane",
	"vehiclesAA",
	"vehiclesLightUnarmed",
	"vehiclesLightArmed",
	"vehiclesAT",
	// ! "vehiclesCivCar",
	// ! "vehiclesCivTruck",
	// ! "vehiclesCivBoat",
	// ! "vehiclesCivHeli",

	// statics
	"staticMortars",
	"staticMGs",
	"staticAT",
	"staticAA",

	// variants
	"variants",

	// identity
	"faces",
	"voices"
];
{
	if (_x in _sharedConfig) then { _convFaction set [_x, _faction get _y, true] };
} forEach _faction;


// * convert highest enemy faction tier loadouts to rebel faction loadouts
private _factionLoadouts = keys (_faction get "loadouts");
private _tierPrefix = {
	if ((_x + "Rifleman") in _factionLoadouts) exitWith {_x};
} forEach ["SF_", "elite_", "military_", "militia_"];

private _rebelUnitTypes = [
	// ! "Petros",
	"Rifleman",
	"ExplosivesExpert",
	"LAT",
	"MachineGunner",
	"SquadLeader",
	// ! "staticCrew",
	"AA",
	"Marksman",
	"Engineer",
	// ! "Unarmed",
	"AT",
	"Sniper",
	"Medic",
	"Grenadier"
];

private _rebelLoadouts = createHashMap;
{
	// * Copy occ / inv loadout to reb loadout
	private _loadout = (_faction get "loadouts") get (_tierPrefix + _x);
	_loadout set [(count _loadout - 1), []];
	_rebelLoadouts set [("militia_" + _x), _loadout, true];


	// ! Can't figure out why this doesn't work when it works in debug console...
	// ! private _loadoutItems = flatten _loadout select {typeName _x != "SCALAR"} select {_x != ""};
	private _loadoutItems = [];
	{
		if ((typeName _x != "SCALAR") && {(_x != "")}) then { _loadoutItems pushBackUnique _x };
	} forEach (flatten _loadout);
	// * Dirty (inefficient) way to populate _initialRebelEquipment: load the same items as in the loadouts
	{
		// ? Should we limit the quantity of the items given, simulating an unsupported / rogue SF unit?
		// ? Would probably make for better gameplay, forcing players to loot from enemy to sustain the war effort, 
		// ? but is tricky to implement.
		private _categories = _x call A3A_fnc_equipmentClassToCategories;
		private _categoriesUnlimited = ["SniperRifle", "Handgun", "Binocular", "Compass", "FirstAidKit", "Map", "Medikit", "Toolkit", "Watch"];
		private _categoriesMostLimited = ["BombLauncher", "GrenadeLauncher", "Launcher", "MissileLauncher", "RocketLauncher", "Explosives"];

		switch true do {
			case ("Uniforms" in _categories): { _rebUniforms pushBackUnique _x};
			case (("Headgear" in _categories) && {!("ArmoredHeadgear" in _categories)}): { _headgear pushBackUnique _x};
			case ((_categories findAny _categoriesUnlimited) != -1): { _initialRebelEquipment pushBackUnique _x };
			case ((_categories findAny _categoriesMostLimited) != -1 ): { _initialRebelEquipment pushBackUnique [_x, 3] };
			default { _initialRebelEquipment pushBackUnique [_x, 10] };
		};
	} forEach _loadoutItems;
} forEach _rebelUnitTypes;
_convFaction set ["loadouts", _rebelLoadouts, true];

// * Manual rebel loadouts
// Petros
private _rebelLoadoutPetros = [[[[],[],[],[selectRandom _rebUniforms,[["FirstAidKit",3],["ACE_EarPlugs",1],["ACE_MapTools",1],["ACE_CableTie",1],["ACE_Flashlight_XL50",1]]],[],[],"",selectRandom _headgear,["Binocular","","","",[],[],""],["ItemMap","","","ItemCompass","ItemWatch",""]]],[],[]];
_convFaction set [(_convFaction get "loadouts") get "militia_Petros", _rebelLoadoutPetros, true];


_convFaction set ["uniforms", _rebUniforms, true];
_convFaction set ["headgear", _headgear, true];



_convFaction;