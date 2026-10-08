/*
function: A3A_fnc_setupImportExportDialog
    Handles the display and import / export funcionality of saved game data introduced with JSON saves.
    This function should only be called from setupImportExportDialog onLoad and control activation EHs.

Author: Creep'nCrunch / jwoodruff40

Environment: Scheduled for onLoad mode / Unscheduled for everything else unless specified

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
#include "..\..\script_component.hpp"
FIX_LINE_NUMBERS()

params ["_mode", "_params"];

Debug_1("Setup Import/Export dialog called with mode %1", _mode);

private _display = findDisplay A3A_IDD_SETUP_IMPORTEXPORTDIALOG;
private _parent = displayParent _display;
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
    };

    case ("onUnload"):
    {
        // ! Stub in case we need to do any cleanup when the dialog is closed
    };

    case ("importData"):
    {
        Info("Attempting to import new save via import / export dialog.");
        
        private _saveData = ctrlText _saveDataBox;
        if (_saveData isEqualTo "") exitWith {
            [localize "STR_antistasi_dialogs_setup_import_export", localize "STR_antistasi_dialogs_setup_ie_import_empty"] call A3A_fnc_customHint;
        };

        private _saveDataHM = fromJSON _saveData;
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
        private _newID = [] call A3A_fnc_generateSaveID;
        _saveDataHM set ["campaignID", _newID];
        Info_2("Registering new save: Old campaignID: %1 | New campaignID: %2 | Name: %3", _campaignID, _newID, _name);

        private _namespace = [profileNamespace, missionProfileNamespace] select (_serverID isEqualTo false);
        _namespace setVariable [format ["A3A_saveData_%1", _newID], _saveDataHM];

        // Update the list of saved games
        private _saveList = [_namespace getVariable "antistasiUltimate2SavedGames"] param [0, [], [[]]];
        _saveList pushBack [_newID, worldName, "Greenfor"]; // * Note: save data does not contain the world name, so the user needs to import the save on the same world in which it was created
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
    };

    case ("toggleEdit"):
    {
        _saveDataBox ctrlEnable !(ctrlEnabled _saveDataBox);
    };

    case ("saveLBPopulate"):
    {
        _params params ["_control", ["_config", configNull]];

        private _allMPNSaves = (allVariables missionProfileNamespace) select { (_x find "a3a_savedata_") isNotEqualTo -1 } apply { [true, _x] };
        private _allPNSaves = (allVariables profileNamespace) select { (_x find "a3a_savedata_") isNotEqualTo -1 } apply { [false, _x] };
        private _allSaves = _allMPNSaves + _allPNSaves;
        {
            private _saveData = [profileNamespace, missionProfileNamespace] select (_x select 0) getVariable (_x select 1);
            private _index = _control lbAdd (_saveData get "name");
            _control lbSetTooltip [_index, _saveData get "gameID"];
            /*
            private _formattedString = ["formatJson", [toJson _saveData]] call A3A_fnc_setupImportExportDialog; // ! commented out because it's slow :/
            _control lbSetData [_index, _formattedString];
            */
            _control lbSetData [_index, toJson _saveData];
        } forEach _allSaves;

        // Resize LB to fit its content
        private _ctrlPos = ctrlPosition _control;
        _ctrlPos set [3, (lbSize _control) * GRID_H * 4];
        _control ctrlSetPosition _ctrlPos;
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

        private _saveDataJson = _control lbData _lbCurSel;
        _saveDataBox ctrlSetText (["formatJson", [_saveDataJson]] call A3A_fnc_setupImportExportDialog);
    };
};
