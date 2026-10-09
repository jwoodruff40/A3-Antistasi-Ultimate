/*
function: A3A_fnc_setupImportExportDialog
    Handles the display and import / export functionality of saved game data.
    This function should only be called from setupImportExportDialog onLoad and control activation EHs.

Author: Creep'nCrunch / jwoodruff40

Environment: Scheduled for onLoad and xxxLBSelChanged modes / Unscheduled for everything else unless specified

Arguments:
    <STRING> Mode, e.g. "onLoad", "importData", etc
    <ARRAY<ANY>> Array of params for the mode when applicable. Params for specific modes are documented in the modes.

Modes:
    - onload called on creation to setup dialog
    - onUnload called on deletion to handle deletion of dialog
    - formatJson params [<STRING> compact JSON, <SCALAR> indent size (default 4)]; returns <STRING> pretty-printed JSON

Return Value:
    Nothing

*/

#include "..\..\dialogues\ids.inc"
#include "..\..\dialogues\defines.hpp"
#include "..\..\script_component.hpp"
FIX_LINE_NUMBERS()

params ["_mode", "_params"];

Debug_1("Setup Import/Export dialog called with mode %1", _mode);

private _display = findDisplay A3A_IDD_SETUP_IMPORTEXPORTDIALOG;
private _parent = displayParent _display;
private _saveDataBoxGroup = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_SAVEDATAGROUP;
private _saveDataBox = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_SAVEDATABOX;
private _importBtn = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_IMPORTBUTTON;
private _exportBtn = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_EXPORTBUTTON;
private _saveListBox = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_SAVELB;

switch (_mode) do
{
    case ("onLoad"):
    {
        // Disable the save data text box to prevent user edits on load until explicitly enabled
        _saveDataBox ctrlEnable false;

        [CBA_EVENT_CLIENT_IMPORTEXPORT_DIALOG_LOADED, [], owner A3A_setupPlayer] call FUNCMAIN(triggerOwnerEvent);
    };

    case ("onUnload"):
    {
        // ! Stub in case we need to do any cleanup when the dialog is closed
    };

    case ("fitText"):
    {
        // The edit box is not scrollable unless its dimensions extend beyond the controls group containing it,
        // so we need to resize it to the size of the text it contains to make it scrollable
        private _saveDataBoxGroup = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_SAVEDATAGROUP;
        private _viewH = (ctrlPosition _saveDataBoxGroup) select 3;
        private _textH = ctrlTextHeight _saveDataBox;
        if (_textH <= 0) then {
            _textH = (count (ctrlText _saveDataBox splitString toString [10]) + 1) * GUI_TEXT_SIZE_EXTRA_SMALL * 1.2;
        };
        private _pos = ctrlPosition _saveDataBox;
        _pos set [3, (_textH + 2 * GRID_H) max _viewH];
        _saveDataBox ctrlSetPosition _pos;
        _saveDataBox ctrlCommit 0;
    };

    case ("fitLB"):
    {
        _params params [["_control", nil, [controlNull]]];
        if (isNil "_control") exitWith {};

        // Resize LB to fit its content
        private _ctrlPos = ctrlPosition _control;
        _ctrlPos set [3, (lbSize _control) * GRID_H * 4];
        _control ctrlSetPosition _ctrlPos;
        _control ctrlCommit 0;
    };

    case ("hashmapToJson"):
    {
        // convert data that doesn't cleanly serialize to JSON into JSON-compatible format
        _params params [["_saveDataHM", nil, [createHashMap]]];

        // convert garage data to JSON-serializable format
        (_saveDataHM get "HR_Garage") params ["_garage", "_UID", "_sources"];
        _garage = _garage apply {
            (toArray _x) params ["_keys", "_values"];
            (_keys apply {str _x}) createHashMapFromArray _values
        };
        _saveDataHM set ["HR_Garage", [_garage, _UID, _sources]];

        // convert mine sides to integers
        private _arrayMines = _saveDataHM get "minesX";
        {
            _x params ["_typeMine", "_posMine", "_detected", "_dirMine"];
            _detected = _detected apply { switch (_x) do {
                case (Invaders): { 0 };
                case (Occupants): { 1 };
                case (teamPlayer): { 2 };
            }};
            _x set [2, _detected];
        } forEach _arrayMines;
        _saveDataHM set ["minesX", _arrayMines];

        [CBA_EVENT_CLIENT_IMPORTEXPORT_HASHMAPTOJSON, [_saveDataHM], owner A3A_setupPlayer] call FUNCMAIN(triggerOwnerEvent);

        toJson _saveDataHM;
    };

    case ("jsonToHashmap"):
    {
        // convert JSON-compatible format back into the original data structure
        _params params [["_saveData", nil, [""]]];

        private _saveDataHM = fromJSON _saveData;

        // convert garage back to original format
        (_saveDataHM get "HR_Garage") params ["_garage", "_UID", "_sources"];
        _garage = _garage apply {
            (toArray _x) params ["_keys", "_values"];
            (_keys apply {if (_x isEqualType "") then { parseNumber _x } else { _x }}) createHashMapFromArray _values
        };
        _saveDataHM set ["HR_Garage", [_garage, _UID, _sources]];

        // convert mine detection back from integers to sides
        private _minesX = _saveDataHM get "minesX";
        {
            _x params ["_typeMine", "_posMine", "_detected", "_dirMine"];
            _detected = _detected apply { switch (_x) do {
                case (0): { Invaders };
                case (1): { Occupants };
                case (2): { teamPlayer };
                default { _x }; // loading old variable data, already stored as a SIDE
            }};
            _x set [2, _detected];
        } forEach (_minesX);
        _saveDataHM set ["minesX", _minesX];

        [CBA_EVENT_CLIENT_IMPORTEXPORT_JSONTOHASHMAP, [_saveDataHM], owner A3A_setupPlayer] call FUNCMAIN(triggerOwnerEvent);

        _saveDataHM;
    };

    case ("importData"):
    {
        // must run on server so data gets saved in server profile (duh),
        // and in the appropriate namespace, depending on server os (which can be (re: probably is) different from the client)
        if (!isServer) exitWith { ["importData"] remoteExecCall ["A3A_fnc_setupImportExportDialog", 2] };

        Info("Attempting to import new save via import / export dialog.");
        
        private _saveData = ctrlText _saveDataBox;
        if (_saveData isEqualTo "") exitWith {
            [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_import_empty"] call A3A_fnc_customHint;
        };

        private _saveDataHM = ["jsonToHashmap", [_saveData]] call A3A_fnc_setupImportExportDialog;
        if (isNil "_saveDataHM" || {!(_saveDataHM isEqualType createHashMap)}) exitWith {
            [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_import_invalid"] call A3A_fnc_customHint;
        };

        // TODO: Validate required keys in the imported save data (e.g., "campaignID", "name", etc)

        ["registerSaveData", [_saveDataHM]] call A3A_fnc_setupImportExportDialog;
    };

    case ("registerSaveData"):
    {
        _params params ["_saveDataHM"];
        
        private _campaignID = _saveDataHM get "campaignID";
        private _serverID = _saveDataHM get "serverID";
        private _name = _saveDataHM get "name";
        private _worldName = _saveDataHM get "worldName";
        private _newID = [] call A3A_fnc_generateSaveID;
        _saveDataHM set ["campaignID", _newID];
        Info_2("Registering new save: Old campaignID: %1 | New campaignID: %2 | Name: %3", _campaignID, _newID, _name);

        private _platformIsWindows = A3A_setup_platform isEqualTo "Windows";
        private _namespace = [profileNamespace, missionProfileNamespace] select (_platformIsWindows);
        _namespace setVariable [format ["A3A_saveData_%1", _newID], _saveDataHM];

        // Update the list of saved games
        private _saveList = [_namespace getVariable "antistasiUltimate2SavedGames"] param [0, [], [[]]];
        _saveList pushBack [_newID, _worldName, "Greenfor"];
        _namespace setVariable ["antistasiUltimate2SavedGames", _saveList];

        if (_serverID isEqualTo false) then { saveMissionProfileNamespace } else { saveProfileNamespace };

        // TODO: Force the setup dialog to show the newly-added save in the loadgame tab; looks like it may require editing fn_initSetupMonitor.fsm

        // Show success message
        [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_import_success"] call A3A_fnc_customHint;
    };

    case ("exportData"):
    {
        copyToClipboard ctrlText _saveDataBox;
        [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_copied"] call A3A_fnc_customHint;
    };

    case ("clearData"):
    {
        _saveDataBox ctrlSetText "";
        _saveListBox lbSetCurSel -1;
        ["fitText"] call A3A_fnc_setupImportExportDialog;
    };

    case ("toggleEdit"):
    {
        _saveDataBox ctrlEnable !(ctrlEnabled _saveDataBox);
        
        // editing disabled so let's assume user added / removed text and we need to resize the edit box
        if (!(ctrlEnabled _saveDataBox)) then { ["fitText"] call A3A_fnc_setupImportExportDialog };
    };

    case ("saveLBPopulate"):
    {
        _params params ["_control", ["_config", configNull]];

        private _allMPNSaves = (allVariables missionProfileNamespace) select { (_x find "a3a_savedata_") isNotEqualTo -1 } apply { [true, _x] };
        private _allPNSaves = (allVariables profileNamespace) select { (_x find "a3a_savedata_") isNotEqualTo -1 } apply { [false, _x] };
        private _allSaves = _allMPNSaves + _allPNSaves;
        {
            private _saveDataHM = [profileNamespace, missionProfileNamespace] select (_x select 0) getVariable (_x select 1);
            private _index = _control lbAdd (_saveDataHM get "name");
            _control lbSetTooltip [_index, _saveDataHM get "gameID"];
            _control lbSetData [_index, ["hashmapToJson", [_saveDataHM]] call A3A_fnc_setupImportExportDialog];
        } forEach _allSaves;

        ["fitLB", [_control]] call A3A_fnc_setupImportExportDialog;
    };

    case ("formatJson"):
    {
        // Pretty-print Json formatter
        _params params ["_json", ["_indentSize", 4]];

        // Work on char codes and one output array to avoid O(n^2) string concatenation
        private _codes = toArray _json;
        private _out = [];
        private _unit = [];
        _unit resize _indentSize;
        _unit = _unit apply { 32 };
        private _indents = [[10]];     // _indents # depth = newline + indentation, built lazily
        private _depth = 0;
        private _inString = false;
        private _escaped = false;
        private _skip = false;

        {
            if (_skip) then {
                _skip = false;
            } else {
                if (_inString) then {
                    _out pushBack _x;
                    if (_escaped) then {
                        _escaped = false;
                    } else {
                        if (_x == 92) then { _escaped = true } else { if (_x == 34) then { _inString = false } };
                    };
                } else {
                    switch (_x) do {
                        case 34: { _out pushBack _x; _inString = true };
                        case 44: {
                            _out pushBack _x;
                            _out append (_indents select _depth);
                        };
                        case 58: { _out pushBack _x; _out pushBack 32 };
                        case 123;
                        case 91: {
                            _out pushBack _x;
                            private _close = [93, 125] select (_x == 123);
                            if ((_codes param [_forEachIndex + 1, -1]) == _close) then {
                                // Keep empty containers compact
                                _out pushBack _close;
                                _skip = true;
                            } else {
                                _depth = _depth + 1;
                                if (count _indents <= _depth) then { _indents pushBack ((_indents select (_depth - 1)) + _unit) };
                                _out append (_indents select _depth);
                            };
                        };
                        case 125;
                        case 93: {
                            _depth = (_depth - 1) max 0;
                            _out append (_indents select _depth);
                            _out pushBack _x;
                        };
                        case 9;
                        case 10;
                        case 13;
                        case 32: {};
                        default { _out pushBack _x };
                    };
                };
            };
        } forEach _codes;

        toString _out
    };

    case ("saveLBSelChanged"):
    {
        _params params ["_control", "_lbCurSel", "_lbSelection"];

        if (_lbCurSel isEqualTo -1) exitWith {};

        private _saveDataLoadingHandle = ["showLoadingAnimation", [localize "STR_antistasi_dialogs_setup_ie_savedata_loading"]] call A3A_fnc_setupImportExportDialog;
        
        private _saveDataJson = _control lbData _lbCurSel;
        private _formattedJson = ["formatJson", [_saveDataJson]] call A3A_fnc_setupImportExportDialog;
        terminate _saveDataLoadingHandle;
        _saveDataBox ctrlSetText _formattedJson;
        ["fitText"] call A3A_fnc_setupImportExportDialog;
        _saveDataBoxGroup ctrlSetScrollValues [0, -1];
    };

    case ("paramLBPopulate"):
    {
        _params params ["_control", ["_config", configNull]];

        private _allPresets = (profileNamespace getVariable "antistasiUltimateCustomParamPresets") toArray false;
        {
            private _index = _control lbAdd (_x select 0);
            _control lbSetData [_index, toJson  [_x select 0, createHashMapFromArray (_x select 1)]];
        } forEach _allPresets;

        ["fitLB", [_control]] call A3A_fnc_setupImportExportDialog;
    };

    case ("paramLBSelChanged"):
    {
        _params params ["_control", "_lbCurSel", "_lbSelection"];

        if (_lbCurSel isEqualTo -1) exitWith {};

        private _paramDataLoadingHandle = ["showLoadingAnimation", [localize "STR_antistasi_dialogs_setup_ie_paramdata_loading"]] call A3A_fnc_setupImportExportDialog;

        private _paramDataJson = _control lbData _lbCurSel;
        private _formattedParamJson = ["formatJson", [_paramDataJson]] call A3A_fnc_setupImportExportDialog;
        terminate _paramDataLoadingHandle;
        _saveDataBox ctrlSetText _formattedParamJson;
        ["fitText"] call A3A_fnc_setupImportExportDialog;
        _saveDataBoxGroup ctrlSetScrollValues [0, -1];
    };

    case ("importParamData"):
    {
        Info("Attempting to import new parameter preset via import / export dialog.");
        
        private _paramData = ctrlText _saveDataBox;
        if (_paramData isEqualTo "") exitWith {
            [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_import_params_empty"] call A3A_fnc_customHint;
        };

        (fromJson _paramData) params ["_presetName", "_paramDataHM"];
        if (isNil "_paramDataHM" || {!(_paramDataHM isEqualType createHashMap)}) exitWith {
            [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_import_params_invalid"] call A3A_fnc_customHint;
        };

        ["savePreset", [_presetName, _paramDataHM toArray false]] call A3A_fnc_setupParamsTab;
        [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_import_param_success"] call A3A_fnc_customHint;
    };

    case ("exportParamData"):
    {
        copyToClipboard ctrlText _saveDataBox;
        [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_params_copied"] call A3A_fnc_customHint;
    };

    case ("showLoadingAnimation"):
    {
        _params params [["_header", nil, [""]]];

        // Show AU logo loading animation while waiting for json formatter
        private _saveDataLoadingHandle = [_saveDataBox, _header] spawn {
            params ["_saveDataBox", "_header"];
            _saveDataBox ctrlSetText (_header + endl);

            private _logoAscii = A3U_LOGO_ASCII;
            private _index = 0;
            while { true } do { 
                sleep 0.1;
                private _text = ctrlText _saveDataBox;
                _saveDataBox ctrlSetText format ["%1%2", _text, _logoAscii select [_index, 4]];
                _index = _index + 4;
                if (_index >= count _logoAscii) then { _index = 0; _saveDataBox ctrlSetText (_header + endl) };
            };
        };
        _saveDataLoadingHandle;
    };
};
