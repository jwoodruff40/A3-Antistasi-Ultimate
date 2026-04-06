#include "..\..\script_component.hpp"
FIX_LINE_NUMBERS()
params ["_vehicle", "_preference"];

/*  Checks if the given vehicle type is within the preferred category
*   Params:
*     _vehicle : STRING : The vehicle type
*     _preference : STRING : The preferred category
*
*   Return:
*     _result : BOOLEAN : True if vehicle fits category, false otherwise
*/

//define list of vehicles as lazy conditions
#define lightVeh \
    {_vehicle in FactionGetAll(occ, "vehiclesLightArmed")} \
    || {_vehicle in FactionGetAll(occ, "vehiclesLightUnarmed")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesLightArmed")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesLightUnarmed")}

#define apc \
    {_vehicle in FactionGetAll(occ, "vehiclesAPCs")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesAPCs")}

#define tank \
    {_vehicle in FactionGetAll(occ, "vehiclesTanks")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesTanks")}

#define patrolHeli \
    {_vehicle in FactionGetAll(occ, "vehiclesHelisLight")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesHelisLight")}

#define transportHeli \
    patrolHeli \
    || {_vehicle in FactionGetAll(occ, "vehiclesHelisTransport")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesHelisTransport")}

#define attackHeli \
    {_vehicle in FactionGetAll(occ, "vehiclesHelisAttack")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesHelisAttack")}

#define drone \
    {_vehicle in FactionGet(occ,"uavsAttack")} \
    || {_vehicle in FactionGet(inv,"uavsAttack")} \
    || {_vehicle in FactionGet(occ,"uavsPortable")} \
    || {_vehicle in FactionGet(inv,"uavsPortable")}

#define plane \
    {_vehicle in FactionGetAll(occ, "vehiclesPlanesCAS")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesPlanesCAS")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesPlanesAA")} \
    || {_vehicle in FactionGetAll(occ, "vehiclesPlanesGunship")} \
	|| {_vehicle in FactionGetAll(occ, "vehiclesPlanesLargeCAS")} \
	|| {_vehicle in FactionGetAll(inv, "vehiclesPlanesLargeAA")} \
	|| {_vehicle in FactionGetAll(occ, "vehiclesPlanesLargeAA")} \
	|| {_vehicle in FactionGetAll(inv, "vehiclesPlanesLargeCAS")} \
    || {_vehicle in FactionGetAll(inv, "vehiclesPlanesGunship")}   

//TODO this does not work properly (maybe even throws errors) as the template files arent
//unified on how they work, await Pots Templates, then fix this
switch (_preference) do
{
    case ("EMPTY"):
    {
      _vehicle == "";
    };
    case ("LAND_START"):
    {
        _vehicle == "" || lightVeh;
    };
    case ("LAND_LIGHT"):
    {
      false || lightVeh;
    };
    case ("LAND_DEFAULT"):
    {
      false || lightVeh || apc;
    };
    case ("LAND_APC"):
    {
      false || apc;
    };
    case ("LAND_ATTACK"):
    {

      false || apc || tank;
    };
    case ("LAND_TANK"):
    {
      false || tank;
    };
    case ("LAND_AIR"):
    {
      _vehicle in FactionGetAll(occ, "vehiclesAA") || {_vehicle in FactionGetAll(inv, "vehiclesAA")};
    };
    case ("HELI_PATROL"):
    {
      _vehicle == "" || patrolHeli;
    };
    case ("HELI_LIGHT"):
    {
      false || patrolHeli;
    };
    case ("HELI_TRANSPORT"):
    {
        false || transportHeli;
    };
    case ("HELI_DEFAULT"):
    {
        false || transportHeli || attackHeli;
    };
    case ("HELI_ATTACK"):
    {
      false || attackHeli;
    };
    case ("AIR_DRONE"):
    {
      _vehicle == "" || drone
    };
    case ("AIR_GENERIC"):
    {
      false || drone || plane;
    };
    case ("AIR_DEFAULT"):
    {
      false || plane;
    };
};
