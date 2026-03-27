/*
Maintainer: DoomMetal
    Handles the New Battle Menu — initialization, tab switching, context bar
    population, context actions, and navigation.
    This function should only be called from newBattleMenu.hpp event handlers
    and control onButtonClick handlers.

Arguments:
    <STRING> _mode    — One of: "onLoad", "onUnload", "handleTabSwitch",
                        "updateContextBar", "handleContextAction", "handleNavigation"
    <ARRAY>  _params  — Mode-specific parameters (see individual cases below)

Return Value:
    Nothing

Scope: Clients, Local Arguments, Local Effect
Environment: Scheduled for "onLoad" / Unscheduled for all other modes
Public: No
Dependencies:
    A3A_fnc_mapDrawOutpostsEH

Examples:
    ["onLoad"]  spawn A3A_fnc_newBattleMenu;
    ["onUnload"] call A3A_fnc_newBattleMenu;
    ["handleTabSwitch",    ["PRIMARY",   "OPERATIONS"]] call A3A_fnc_newBattleMenu;
    ["handleTabSwitch",    ["SECONDARY", 2]]            call A3A_fnc_newBattleMenu;
    ["updateContextBar",   ["OPERATIONS", 1]]           call A3A_fnc_newBattleMenu;
    ["handleContextAction",["CONTEXT_ACTION_1"]]        call A3A_fnc_newBattleMenu;
    ["handleNavigation",   ["NAV_HOME"]]                call A3A_fnc_newBattleMenu;
*/

#include "..\..\dialogues\ids.inc"
#include "..\..\dialogues\defines.hpp"
#include "..\..\script_component.hpp"
FIX_LINE_NUMBERS()

params [["_mode", "onLoad"], ["_params", []]];

private _display = findDisplay A3A_IDD_NEWBATTLEMENU;

// Active theme highlight color (matches button hover EH in controls.hpp).
private _colorActive = [
    profilenamespace getVariable ["GUI_BCG_RGB_R", 0.13],
    profilenamespace getVariable ["GUI_BCG_RGB_G", 0.54],
    profilenamespace getVariable ["GUI_BCG_RGB_B", 0.21],
    profilenamespace getVariable ["GUI_BCG_RGB_A", 0.8]
];
private _colorInactive = [0, 0, 0, 1];

switch (_mode) do
{
    // -----------------------------------------------------------------------
    case "onLoad":
    {
        Debug("NewBattleMenu onLoad starting...");

        // Hide HC group icons to stop them from interfering with map controls.
        _display setVariable ["HCgroupIcons", groupIconsVisible];
        setGroupIconsVisible [false, false];
        setGroupIconsSelectable false;

        // Add outpost draw EH to the battle map.
        private _map = _display displayCtrl A3A_IDC_NEWBATTLEMENU_MAP;
        _map ctrlAddEventHandler ["Draw", "_this call A3A_fnc_mapDrawOutpostsEH"];

        // Switch to the saved default tab (or Operations if not set).
        private _defaultTab = profileNamespace getVariable ["A3A_newBattleMenu_defaultTab", "OPERATIONS"];
        ["handleTabSwitch", ["PRIMARY", _defaultTab]] call A3A_fnc_newBattleMenu;

        Debug("NewBattleMenu onLoad complete.");
    };

    // -----------------------------------------------------------------------
    case "onUnload":
    {
        Debug("NewBattleMenu onUnload starting...");

        // Remove map drawing event handlers.
        private _map = _display displayCtrl A3A_IDC_NEWBATTLEMENU_MAP;
        _map ctrlRemoveAllEventHandlers "Draw";

        // Restore HC group icons state.
        private _groupIcons = _display getVariable ["HCgroupIcons", [false, false]];
        setGroupIconsVisible _groupIcons;
        setGroupIconsSelectable true;

        Debug("NewBattleMenu onUnload complete.");
    };

    // -----------------------------------------------------------------------
    // handleTabSwitch
    //   _params select 0: <STRING> "PRIMARY" or "SECONDARY"
    //   _params select 1: <STRING> section name  (PRIMARY)
    //                  or <NUMBER> button index 1..4 (SECONDARY)
    case "handleTabSwitch":
    {
        _params params ["_type", "_value"];

        switch (_type) do
        {
            case "PRIMARY":
            {
                private _tab = _value;
                Debug_1("NewBattleMenu: switching primary tab to %1", _tab);

                // Store active section for secondary/context handlers.
                _display setVariable ["activePrimaryTab", _tab];

                // Highlight the clicked primary tab; reset the others.
                private _primaryTabIDCs = [
                    A3A_IDC_NEWBATTLEMENU_TAB_OPERATIONS,
                    A3A_IDC_NEWBATTLEMENU_TAB_SUPPORTS,
                    A3A_IDC_NEWBATTLEMENU_TAB_PERSONNEL,
                    A3A_IDC_NEWBATTLEMENU_TAB_CONTEXT
                ];
                private _activeTabIDC = switch (_tab) do
                {
                    case "OPERATIONS": { A3A_IDC_NEWBATTLEMENU_TAB_OPERATIONS };
                    case "SUPPORTS":   { A3A_IDC_NEWBATTLEMENU_TAB_SUPPORTS };
                    case "PERSONNEL":  { A3A_IDC_NEWBATTLEMENU_TAB_PERSONNEL };
                    case "CONTEXT":    { A3A_IDC_NEWBATTLEMENU_TAB_CONTEXT };
                    default            { -1 };
                };
                {
                    (_display displayCtrl _x) ctrlSetBackgroundColor (
                        if (_x == _activeTabIDC) then {_colorActive} else {_colorInactive}
                    );
                } forEach _primaryTabIDCs;

                // CONTEXT tab: show RightPanelContextContainer, hide secondary tabs.
                // All other tabs: show secondary tabs, hide context panel.
                private _secondaryTabsCtrl = _display displayCtrl A3A_IDC_NEWBATTLEMENU_MAINTABS;
                private _contextPanelCtrl  = _display displayCtrl A3A_IDC_NEWBATTLEMENU_RIGHTPANEL_CONTEXT;
                private _isContext = _tab == "CONTEXT";
                _secondaryTabsCtrl ctrlShow !_isContext;
                _contextPanelCtrl  ctrlShow  _isContext;

                if (!_isContext) then
                {
                    // Relabel secondary tab buttons for the new section.
                    private _btn1 = _display displayCtrl A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN1;
                    private _btn2 = _display displayCtrl A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN2;
                    private _btn3 = _display displayCtrl A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN3;
                    private _btn4 = _display displayCtrl A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN4;

                    private _labels = switch (_tab) do
                    {
                        case "OPERATIONS": {[
                            localize "STR_antistasi_dialogs_new_battle_menu_hq_mgmt_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_garrison_mgmt_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_emplacement_mgmt_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_mission_mgmt_button"
                        ]};
                        case "SUPPORTS": {[
                            localize "STR_antistasi_dialogs_new_battle_menu_offensive_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_defensive_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_recon_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_supply_button"
                        ]};
                        case "PERSONNEL": {[
                            localize "STR_antistasi_dialogs_new_battle_menu_player_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_commander_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_ai_recruit_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_ai_mgmt_button"
                        ]};
                        case "GAME_OPTIONS": {[
                            localize "STR_antistasi_dialogs_new_battle_menu_environment_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_performance_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_server_info_button",
                            localize "STR_antistasi_dialogs_new_battle_menu_save_button"
                        ]};
                        case "SETTINGS": {[
                            localize "STR_antistasi_dialogs_new_battle_menu_default_tab_button",
                            "", "", ""
                        ]};
                        default { ["", "", "", ""] };
                    };

                    _btn1 ctrlSetText (_labels select 0);
                    _btn2 ctrlSetText (_labels select 1);
                    _btn3 ctrlSetText (_labels select 2);
                    _btn4 ctrlSetText (_labels select 3);

                    // SETTINGS only has one meaningful secondary tab — hide the rest.
                    private _isSettings = _tab == "SETTINGS";
                    _btn2 ctrlShow !_isSettings;
                    _btn3 ctrlShow !_isSettings;
                    _btn4 ctrlShow !_isSettings;

                    // Auto-select the first secondary tab.
                    ["handleTabSwitch", ["SECONDARY", 1]] call A3A_fnc_newBattleMenu;
                };
            };

            case "SECONDARY":
            {
                private _index = _value;
                private _activePrimaryTab = _display getVariable ["activePrimaryTab", "OPERATIONS"];

                Debug_2("NewBattleMenu: switching secondary tab to %1 (primary: %2)", _index, _activePrimaryTab);

                // Store for context action and navigation handlers.
                _display setVariable ["activeSecondaryIndex", _index];

                // Highlight the active secondary tab; reset the others.
                private _secondaryBtnIDCs = [
                    A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN1,
                    A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN2,
                    A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN3,
                    A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN4
                ];
                {
                    (_display displayCtrl _x) ctrlSetBackgroundColor (
                        if (_forEachIndex + 1 == _index) then {_colorActive} else {_colorInactive}
                    );
                } forEach _secondaryBtnIDCs;

                // Populate the context bar for this primary/secondary combination.
                ["updateContextBar", [_activePrimaryTab, _index]] call A3A_fnc_newBattleMenu;
            };
        };
    };

    // -----------------------------------------------------------------------
    // updateContextBar
    //   _params select 0: <STRING> active primary tab name
    //   _params select 1: <NUMBER> active secondary tab index (1..4)
    case "updateContextBar":
    {
        _params params ["_primaryTab", "_secondaryIndex"];

        Debug_2("NewBattleMenu: updateContextBar primary=%1 secondary=%2", _primaryTab, _secondaryIndex);

        private _contextBtnIDCs = [
            A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON1,  A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON2,
            A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON3,  A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON4,
            A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON5,  A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON6,
            A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON7,  A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON8,
            A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON9,  A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON10,
            A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON11, A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON12
        ];

        // Clear all buttons first; show only the ones that are populated below.
        {
            private _btn = _display displayCtrl _x;
            _btn ctrlSetText "";
            _btn ctrlShow false;
        } forEach _contextBtnIDCs;

        // Build the label/action list for the current primary+secondary combination.
        // Each entry is [label, actionCode] where actionCode is a short string
        // dispatched in handleContextAction.  Empty/missing slots remain hidden.
        private _actions = [];

        switch (_primaryTab) do
        {
            // ── OPERATIONS ──────────────────────────────────────────────────
            case "OPERATIONS":
            {
                switch (_secondaryIndex) do
                {
                    // HQ Management
                    case 1: {
                        _actions = [
                            ["Move HQ",             "OP_MOVE_HQ"],
                            ["Train Rebel Troops",  "OP_TRAIN_TROOPS"],
                            ["Set Rebel Loadouts",  "OP_REL_LOADOUTS"],
                            ["Clear Forest",        "OP_CLEAR_FOREST"]
                        ];
                    };
                    // Garrison Management
                    case 2: {
                        _actions = [
                            ["Disband Units/Post",  "OP_DISBAND"],
                            ["Recruit Units",       "OP_RECRUIT"]
                        ];
                    };
                    // Emplacement Management
                    case 3: {
                        _actions = [
                            ["Establish Watchpost",        "OP_EST_WATCHPOST"],
                            ["Establish Roadblock",        "OP_EST_ROADBLOCK"],
                            ["Establish HMG Emplacement",  "OP_EST_HMG"],
                            ["Establish AT Emplacement",   "OP_EST_AT"],
                            ["Establish AA Emplacement",   "OP_EST_AA"],
                            ["Establish AP Minefield",     "OP_MINE_AP"],
                            ["Establish AT Minefield",     "OP_MINE_AT"]
                        ];
                    };
                    // Mission Management
                    case 4: {
                        _actions = [
                            ["Request Assassination", "OP_MISS_AS"],
                            ["Request Convoy",        "OP_MISS_CONVOY"],
                            ["Request Destroy",       "OP_MISS_DES"],
                            ["Request Logistics",     "OP_MISS_LOG"],
                            ["Request Rescue",        "OP_MISS_RES"],
                            ["Request Conquest",      "OP_MISS_CON"],
                            ["Request Supply",        "OP_MISS_SUPP"]
                        ];
                    };
                };
            };

            // ── SUPPORTS ────────────────────────────────────────────────────
            case "SUPPORTS":
            {
                switch (_secondaryIndex) do
                {
                    // Offensive
                    case 1: {
                        _actions = [
                            ["HE Bomb Airstrike",      "SUP_HE"],
                            ["Cluster Bomb Airstrike", "SUP_CLUSTER"],
                            ["Chemical Bomb Airstrike","SUP_CHEM"],
                            ["Napalm Airstrike",       "SUP_NAPALM"],
                            ["Paradrop Plane Run",     "SUP_PARADROP"]
                        ];
                    };
                    // Defensive
                    case 2: {
                        _actions = [
                            ["Smoke Barrage",  "SUP_SMOKE"],
                            ["Flare Barrage",  "SUP_FLARE"]
                        ];
                    };
                    // Reconnaissance
                    case 3: {
                        _actions = [
                            ["Recon Plane Run", "SUP_RECON"]
                        ];
                    };
                    // Supply
                    case 4: {
                        _actions = [
                            ["Light Vehicle Airdrop",  "SUP_VEH_AIRDROP"],
                            ["Supply Crate Airdrop",   "SUP_SUPPLY"],
                            ["Loot Helicopter Run",    "SUP_LOOTHELI"]
                        ];
                    };
                };
            };

            // ── PERSONNEL ───────────────────────────────────────────────────
            case "PERSONNEL":
            {
                switch (_secondaryIndex) do
                {
                    // Player
                    case 1: {
                        _actions = [
                            ["Toggle Music",       "PER_MUSIC"],
                            ["Toggle Paradrop",    "PER_PARADROP"],
                            ["Toggle Teardown",    "PER_TEARDOWN"],
                            ["Donate Money",       "PER_DONATE"]
                        ];
                    };
                    // Commander
                    case 2: {
                        _actions = [
                            ["Check Victory",           "PER_CMD_VICTORY"],
                            ["Reset Arms Dealer",       "PER_CMD_RESET_TRADER"],
                            ["Train Rebel Troops",      "PER_CMD_TRAIN"],
                            ["Set Rebel Loadouts",      "PER_CMD_LOADOUTS"],
                            ["Set Arsenal Limits",      "PER_CMD_ARSENAL"],
                            ["Place/Remove Rally Point","PER_CMD_RALLY"],
                            ["Share Faction Money",     "PER_CMD_SHARE_MONEY"],
                            ["Resign / Toggle Elig.",   "PER_CMD_RESIGN"],
                            ["Add Server Member",       "PER_CMD_ADD_MEMBER"],
                            ["Remove Server Member",    "PER_CMD_REM_MEMBER"]
                        ];
                    };
                    // AI Recruitment
                    case 3: {
                        _actions = [
                            ["Infantry Squad",  "PER_REC_INF_SQUAD"],
                            ["Infantry Team",   "PER_REC_INF_TEAM"],
                            ["AT Team",         "PER_REC_AT_TEAM"],
                            ["AT Car",          "PER_REC_AT_CAR"],
                            ["Snipers",         "PER_REC_SNIPER"],
                            ["AA Truck",        "PER_REC_AA_TRUCK"],
                            ["MG Team",         "PER_REC_MG_TEAM"],
                            ["Mortar Team",     "PER_REC_MORTAR"],
                            ["Vehicle Crew",    "PER_REC_VEH_CREW"],
                            ["MG Car",          "PER_REC_MG_CAR"]
                        ];
                    };
                    // AI Management
                    case 4: {
                        _actions = [
                            ["AI Control",          "PER_AI_CONTROL"],
                            ["HC Transfer",         "PER_AI_HC"],
                            ["Garrison Unit/Squad", "PER_AI_GARRISON"],
                            ["Dismiss Unit/Squad",  "PER_AI_DISMISS"],
                            ["Auto Rearm/Loot",     "PER_AI_REARM"],
                            ["SITREP",              "PER_AI_SITREP"],
                            ["Assign Vehicle",      "PER_AI_ASSIGN_VEH"],
                            ["(Dis)mount Vehicle",  "PER_AI_MOUNT"]
                        ];
                    };
                };
            };

            // ── GAME_OPTIONS ─────────────────────────────────────────────────
            case "GAME_OPTIONS":
            {
                switch (_secondaryIndex) do
                {
                    // Environment
                    case 1: {
                        _actions = [
                            ["Set Fog Level",      "OPT_FOG"],
                            ["Set Overcast Level", "OPT_OVERCAST"]
                        ];
                    };
                    // Performance
                    case 2: {
                        _actions = [
                            ["Garbage Clean", "OPT_GARBAGE"]
                        ];
                    };
                    // Server Info — display-only, no action buttons
                    case 3: {
                        _actions = [];
                    };
                    // Save
                    case 4: {
                        _actions = [
                            ["Persistent Save",     "OPT_SAVE"],
                            ["Edit Save Params",    "OPT_EDIT_PARAMS"]
                        ];
                    };
                };
            };

            // ── SETTINGS ─────────────────────────────────────────────────────
            case "SETTINGS":
            {
                // Default Tab (index 1 only)
                _actions = [
                    ["Operations", "SET_DEFAULT_OPERATIONS"],
                    ["Supports",   "SET_DEFAULT_SUPPORTS"],
                    ["Personnel",  "SET_DEFAULT_PERSONNEL"],
                    ["Context",    "SET_DEFAULT_CONTEXT"]
                ];
            };
        };

        // Store the active action codes so handleContextAction can dispatch them.
        _display setVariable ["contextActionCodes", _actions apply { _x select 1 }];

        // Show and label each slot that has an entry.
        {
            _x params ["_label", "_actionCode"];
            private _btn = _display displayCtrl (_contextBtnIDCs select _forEachIndex);
            _btn ctrlSetText _label;
            _btn ctrlShow true;
        } forEach _actions;
    };

    // -----------------------------------------------------------------------
    // handleContextAction
    //   _params select 0: <STRING> action identifier (e.g. "CONTEXT_ACTION_1")
    case "handleContextAction":
    {
        _params params ["_action"];

        Debug_1("NewBattleMenu: handleContextAction called with %1", _action);

        // Extract the trailing slot number from "CONTEXT_ACTION_N".
        private _slotNum = parseNumber (_action select [count "CONTEXT_ACTION_"]);

        // Retrieve the ordered action-code list stored by updateContextBar.
        private _actionCodes = _display getVariable ["contextActionCodes", []];
        if (_slotNum < 1 || _slotNum > count _actionCodes) exitWith {
            Debug_1("NewBattleMenu: handleContextAction - slot %1 out of range", _slotNum);
        };
        private _code = _actionCodes select (_slotNum - 1);

        Debug_1("NewBattleMenu: dispatching action code %1", _code);

        switch (_code) do
        {
            // ── OPERATIONS / HQ Management ──────────────────────────────────
            case "OP_MOVE_HQ":       { closeDialog 0; [] spawn A3A_fnc_moveHQ; };
            case "OP_TRAIN_TROOPS":  { [] spawn A3A_fnc_FIAskillAdd; };
            case "OP_REL_LOADOUTS":  { [] call SCRT_fnc_ui_createRebelLoadoutMenu; };
            case "OP_CLEAR_FOREST":  { [] call A3A_fnc_clearForest; closeDialog 0; };

            // ── OPERATIONS / Garrison Management ────────────────────────────
            case "OP_DISBAND":       { [] call SCRT_fnc_ui_setDisbandMode; };
            case "OP_RECRUIT":       { [] call SCRT_fnc_ui_setRecruitMode; };

            // ── OPERATIONS / Emplacement Management ─────────────────────────
            // Outpost type is set via a separate combobox before calling
            // setEstablishOutpostMode; all placement types share the same entry.
            case "OP_EST_WATCHPOST";
            case "OP_EST_ROADBLOCK";
            case "OP_EST_HMG";
            case "OP_EST_AT";
            case "OP_EST_AA":        { [] call SCRT_fnc_ui_setEstablishOutpostMode; };
            case "OP_MINE_AP";
            case "OP_MINE_AT":       { [] call SCRT_fnc_ui_setMinefieldMode; };

            // ── OPERATIONS / Mission Management ─────────────────────────────
            case "OP_MISS_AS";
            case "OP_MISS_CONVOY";
            case "OP_MISS_DES";
            case "OP_MISS_LOG";
            case "OP_MISS_RES";
            case "OP_MISS_CON";
            case "OP_MISS_SUPP": { closeDialog 0; if ((player call A3A_fnc_isMember) or (!(isPlayer theBoss))) then { [_code select [8],  clientOwner] remoteExec ["A3A_fnc_missionRequest", 2] } else { ["Mission Request", "Commander only"] call A3A_fnc_customHint }; };

            // ── SUPPORTS — each sets the global supportType then launches ───
            case "SUP_HE";
            case "SUP_CLUSTER";
            case "SUP_CHEM";
            case "SUP_NAPALM";
            case "SUP_PARADROP";
            case "SUP_SMOKE";
            case "SUP_FLARE";
            case "SUP_RECON";
            case "SUP_VEH_AIRDROP";
            case "SUP_SUPPLY";
            case "SUP_LOOTHELI":    { supportType = _code select [4];    closeDialog 0; [] spawn SCRT_fnc_ui_launchSupport; };

            // ── PERSONNEL / Player ───────────────────────────────────────────
            case "PER_MUSIC":    { ["MAIN", 5100, true, "MUSIC"]    call SCRT_fnc_ui_switchButton; };
            case "PER_PARADROP": { ["MAIN", 5400, true, "PARADROP"] call SCRT_fnc_ui_switchButton; };
            case "PER_TEARDOWN": { while {dialog} do { closeDialog 0 }; [] call A3A_fnc_toggleTeardownMode; };
            case "PER_DONATE":   { closeDialog 0; ["switchTab", ["donate"]] call A3A_fnc_mainDialog; };

            // ── PERSONNEL / Commander ────────────────────────────────────────
            case "PER_CMD_VICTORY":      { closeDialog 0; [] spawn A3A_fnc_checkWinCondition; };
            case "PER_CMD_RESET_TRADER": { if (player isEqualTo theBoss) then { closeDialog 0; [] spawn SCRT_fnc_trader_rerollTrader } else { ["Commander only", "Only the Commander can reset the arms dealer"] call A3A_fnc_customHint }; };
            case "PER_CMD_TRAIN":        { [] spawn A3A_fnc_FIAskillAdd; };
            case "PER_CMD_LOADOUTS":     { [] call SCRT_fnc_ui_createRebelLoadoutMenu; };
            case "PER_CMD_ARSENAL":      { if (player == theBoss) then { closeDialog 0; createDialog "A3A_ArsenalLimitsDialog" } else { ["Arsenal Limits", "Only the Commander can change arsenal limits"] call A3A_fnc_customHint }; };
            case "PER_CMD_RALLY":        { if (player isEqualTo theBoss) then { closeDialog 0; [] call SCRT_fnc_rally_toggleRallyPoint } else { ["Rally Point", "Only the Commander can manage rally points"] call A3A_fnc_customHint }; };
            case "PER_CMD_SHARE_MONEY":  { if (player isEqualTo theBoss) then { closeDialog 0; [] call SCRT_fnc_common_shareFactionMoneyWithMembers } else { ["Share Money", "Only the Commander can share faction money"] call A3A_fnc_customHint }; };
            case "PER_CMD_RESIGN":       { closeDialog 0; [player, cursorTarget] remoteExec ["A3A_fnc_theBossToggleEligibility", 2]; };
            case "PER_CMD_ADD_MEMBER":   { closeDialog 0; ["add"]    call A3A_fnc_memberAdd; };
            case "PER_CMD_REM_MEMBER":   { closeDialog 0; ["remove"] call A3A_fnc_memberAdd; };

            // ── PERSONNEL / AI Recruitment ───────────────────────────────────
            // Opens the recruit squad dialog with the appropriate squad type slot selected.
            case "PER_REC_INF_SQUAD";
            case "PER_REC_INF_TEAM";
            case "PER_REC_AT_TEAM";
            case "PER_REC_AT_CAR";
            case "PER_REC_SNIPER";
            case "PER_REC_AA_TRUCK";
            case "PER_REC_MG_TEAM";
            case "PER_REC_MORTAR";
            case "PER_REC_VEH_CREW";
            case "PER_REC_MG_CAR":    { createDialog "A3A_RecruitSquadDialog"; };

            // ── PERSONNEL / AI Management ────────────────────────────────────
            case "PER_AI_CONTROL": {
                closeDialog 0;
                if ((count groupselectedUnits player > 0) and (count hcSelected player > 0)) exitWith {
                    ["AI Control", "Select only AI units OR HC squads, not both"] call A3A_fnc_customHint;
                };
                if (count groupselectedUnits player == 1) then { [groupselectedUnits player] spawn A3A_fnc_controlUnit };
                if (count hcSelected player == 1) then { [hcSelected player] spawn A3A_fnc_controlHCsquad };
            };
            case "PER_AI_HC":      { closeDialog 0; [] call SCRT_fnc_common_hcTransfer; };
            case "PER_AI_GARRISON": {
                closeDialog 0;
                if (count groupselectedUnits player > 0) then { [groupselectedUnits player] spawn A3A_fnc_addToGarrison }
                else { if (count (hcSelected player) > 0) then { [hcSelected player] spawn A3A_fnc_addToGarrison } };
                if ((count groupselectedUnits player == 0) and (count hcSelected player == 0)) then {
                    ["Garrison Unit/Squad", "No units or squads selected"] call A3A_fnc_customHint;
                };
            };
            case "PER_AI_DISMISS": {
                closeDialog 0;
                if (count groupselectedUnits player > 0) then { [groupselectedUnits player] spawn A3A_fnc_dismissPlayerGroup }
                else { if (count (hcSelected player) > 0) then { [hcSelected player] spawn A3A_fnc_dismissSquad } };
                if ((count groupselectedUnits player == 0) and (count hcSelected player == 0)) then {
                    ["Dismiss Unit/Squad", "No units or squads selected"] call A3A_fnc_customHint;
                };
            };
            case "PER_AI_REARM": {
                closeDialog 0;
                if (count groupselectedUnits player == 0) then { (units group player) spawn A3A_fnc_rearmCall }
                else { (groupselectedUnits player) spawn A3A_fnc_rearmCall };
            };
            case "PER_AI_SITREP":      { closeDialog 0; ["stats"] call A3A_fnc_vehStats; };
            case "PER_AI_ASSIGN_VEH":  { closeDialog 0; [] call A3A_fnc_addSquadVeh; };
            case "PER_AI_MOUNT":       { closeDialog 0; ["mount"] call A3A_fnc_vehStats; };

            // ── GAME_OPTIONS / Environment ───────────────────────────────────
            case "OPT_FOG": {
                if (player isEqualTo theBoss) then {
                    [10, fogValue] remoteExec ["setFog", 2];
                } else {
                    ["Set Fog", "Only the Commander can change weather"] call A3A_fnc_customHint;
                };
            };
            case "OPT_OVERCAST": {
                if (player isEqualTo theBoss) then {
                    [] spawn { [overcastValue] call BIS_fnc_setOvercast };
                } else {
                    ["Set Overcast", "Only the Commander can change weather"] call A3A_fnc_customHint;
                };
            };

            // ── GAME_OPTIONS / Performance ───────────────────────────────────
            case "OPT_GARBAGE": {
                if (player isEqualTo theBoss) then {
                    closeDialog 0; [] remoteExecCall ["A3A_fnc_garbageCleaner", 2];
                } else {
                    ["Garbage Cleaner", "Only the Commander can run garbage cleaner"] call A3A_fnc_customHint;
                };
            };

            // ── GAME_OPTIONS / Save ──────────────────────────────────────────
            case "OPT_SAVE":        { closeDialog 0; [] spawn A3A_fnc_persistentSave; };
            case "OPT_EDIT_PARAMS": { ["onLoad"] spawn SCRT_fnc_ui_editParamsMenu; };

            // ── SETTINGS / Default Tab ───────────────────────────────────────
            // Store the preferred opening tab in profileNamespace.
            case "SET_DEFAULT_OPERATIONS": { profileNamespace setVariable ["A3A_newBattleMenu_defaultTab", "OPERATIONS"]; saveProfileNamespace; };
            case "SET_DEFAULT_SUPPORTS":   { profileNamespace setVariable ["A3A_newBattleMenu_defaultTab", "SUPPORTS"];   saveProfileNamespace; };
            case "SET_DEFAULT_PERSONNEL":  { profileNamespace setVariable ["A3A_newBattleMenu_defaultTab", "PERSONNEL"];  saveProfileNamespace; };
            case "SET_DEFAULT_CONTEXT":    { profileNamespace setVariable ["A3A_newBattleMenu_defaultTab", "CONTEXT"];    saveProfileNamespace; };

            default {
                Error_1("NewBattleMenu: handleContextAction - unknown action code '%1'", _code);
            };
        };
    };

    // -----------------------------------------------------------------------
    // handleNavigation
    //   _params select 0: <STRING> "NAV_BACK", "NAV_HOME", or "NAV_MENU"
    case "handleNavigation":
    {
        _params params ["_action"];

        Debug_1("NewBattleMenu: handleNavigation called with %1", _action);

        switch (_action) do
        {
            case "NAV_BACK":
            {
                // TODO: Navigate back to the previous secondary/primary tab.
            };

            case "NAV_HOME":
            {
                // Return to Operations / HQ Management (the default open state).
                ["handleTabSwitch", ["PRIMARY", "OPERATIONS"]] call A3A_fnc_newBattleMenu;
            };

            case "NAV_MENU":
            {
                closeDialog 0;
            };
        };
    };
};
