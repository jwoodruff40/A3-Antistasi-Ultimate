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

        // Switch to the Operations primary tab by default.
        ["handleTabSwitch", ["PRIMARY", "OPERATIONS"]] call A3A_fnc_newBattleMenu;

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

        // TODO: Implement per-combination button population using the
        //       action definitions from the UI specification.
    };

    // -----------------------------------------------------------------------
    // handleContextAction
    //   _params select 0: <STRING> action identifier (e.g. "CONTEXT_ACTION_1")
    case "handleContextAction":
    {
        _params params ["_action"];

        Debug_1("NewBattleMenu: handleContextAction called with %1", _action);

        // TODO: Route _action to the appropriate game function based on the
        //       activePrimaryTab / activeSecondaryIndex stored in the display.
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
