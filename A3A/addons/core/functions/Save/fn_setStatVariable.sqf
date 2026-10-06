
params ["_varName", "_varValue", ["_final", false]];
A3A_saveTarget params ["_serverID", "_campaignID", "_map"];

if (isNil "_varValue") exitWith {};			// hmm...

// Store data in temporary hashmap until we're done adding all the data, then save the entire save data as one hashmap to the appropriate namespace
if (!_final && {!isNil {A3A_saveDataHM} && {A3A_saveDataHM isEqualType createHashMap}}) exitWith {
	A3A_saveDataHM set [_varName, _varValue];
};

private _namespace = [profileNamespace, missionProfileNamespace] select (_serverID isEqualTo false);
_namespace setVariable [format ["%1%2", _varName, _campaignID], _varValue];
