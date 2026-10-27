/*
  Main Dialog - aka the Y-menu
*/

#include "ids.inc"

class A3A_MainDialog : A3A_TabbedDialog
{
    idd = A3A_IDD_MAINDIALOG;
    onLoad = "[""onLoad""] spawn A3A_fnc_mainDialog";
    onUnload = "[""onUnload""] call A3A_fnc_mainDialog";

    class Controls
    {
        class TitlebarText : A3A_TitlebarText
        {
            idc = A3A_IDC_MAINDIALOGTITLEBAR;
            text = "$STR_antistasi_dialogs_main_titlebar";
            x = QUOTE(DIALOG_X);
            y = QUOTE(DIALOG_Y - 10 * GRID_H);
            w = QUOTE(DIALOG_W * GRID_W);
            h = QUOTE(5 * GRID_H);
        };

        class TabButtons : A3A_ControlsGroupNoScrollbars
        {
            idc = A3A_IDC_MAINDIALOGTABBUTTONS;
            x = QUOTE(DIALOG_X);
            y = QUOTE(DIALOG_Y - 5 * GRID_H);
            w = QUOTE(DIALOG_W * GRID_W);
            h = QUOTE(5 * GRID_H);

            class Controls
            {
                class PlayerTabButton : A3A_Button
                {
                    idc = A3A_IDC_PLAYERTABBUTTON;
                    text = "$STR_antistasi_dialogs_main_player_tab_button";
                    onButtonClick = "[""switchTab"", [""player""]] call A3A_fnc_mainDialog;";
                    x = 0;
                    y = 0;
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(5 * GRID_H);
                };

                class CommanderTabButton : A3A_Button
                {
                    idc = A3A_IDC_COMMANDERTABBUTTON;
                    text = "$STR_antistasi_dialogs_main_commander_tab_button";
                    onButtonClick = "[""switchTab"", [""commander""]] call A3A_fnc_mainDialog;";
                    x = QUOTE(30 * GRID_W);
                    y = 0;
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(5 * GRID_H);
                };

                class AdminTabButton : A3A_Button
                {
                    idc = A3A_IDC_ADMINTABBUTTON;
                    text = "$STR_antistasi_dialogs_main_admin_tab_button";
                    onButtonClick = "[""switchTab"", [""admin""]] call A3A_fnc_mainDialog;";
                    x = QUOTE(60 * GRID_W);
                    y = 0;
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(5 * GRID_H);
                };
            };
        };


        ///////////////
        // MAIN TABS //
        ///////////////

        class PlayerTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_PLAYERTAB;
            show = 0;

            class Controls
            {
                // Left side button column

                // Undercover
                class UndercoverIcon : A3A_Picture
                {
                    idc = A3A_IDC_UNDERCOVERICON;
                    text = A3A_Icon_Undercover;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(13 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class UndercoverButton : A3A_Button
                {
                    idc = A3A_IDC_UNDERCOVERBUTTON;
                    text = "$STR_antistasi_dialogs_main_undercover";
                    // onButtonClick = "[] call A3A_fnc_goUndercover; closeDialog 0";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(11 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                // Fast Travel
                class FastTravelIcon : A3A_Picture
                {
                    idc = A3A_IDC_FASTTRAVELICON;
                    text = A3A_Icon_FastTravel;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(34 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class FastTravelButton : A3A_Button
                {
                    idc = A3A_IDC_FASTTRAVELBUTTON;
                    text = "$STR_antistasi_dialogs_main_fast_travel";
                    tooltip = "$STR_antistasi_dialogs_main_fast_travel_tooltip";
                    onButtonClick = "[""setHcMode"", [false]] call A3A_fnc_fastTravelTab; [""switchTab"", [""fasttravel""]] call A3A_fnc_mainDialog";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(32 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                // Construct
                class ConstructIcon : A3A_Picture
                {
                    idc = A3A_IDC_CONSTRUCTICON;
                    text = A3A_Icon_Construct;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(55 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class ConstructButton : A3A_Button
                {
                    idc = A3A_IDC_CONSTRUCTBUTTON;
                    text = "$STR_antistasi_dialogs_main_construct";
                    onButtonClick = "[""switchTab"", [""construct""]] call A3A_fnc_mainDialog;";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                // AI Management
                class AIManagementIcon : A3A_Picture
                {
                    idc = A3A_IDC_AIMANAGEMENTICON;
                    text = A3A_Icon_AI_Management;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(76 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class AIManagementButton : A3A_Button
                {
                    idc = A3A_IDC_AIMANAGEMENTBUTTON;
                    text = "$STR_antistasi_dialogs_main_ai_management";
                    onButtonClick = "[""switchTab"", [""aimanagement""]] call A3A_fnc_mainDialog;";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(74 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };


                // Right side content

                // Player info area
                class PlayerNameText : A3A_Text
                {
                    idc = A3A_IDC_PLAYERNAMETEXT;
                    text = "";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    colorBackground[] = A3A_COLOR_BLACK;
                    x = QUOTE(70 * GRID_W);
                    y = QUOTE(7 * GRID_H);
                    w = QUOTE(90 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class PlayerRankText : A3A_Text
                {
                    idc = A3A_IDC_PLAYERRANKTEXT;
                    colorText[] = A3A_COLOR_TEXT_DARKER;
                    style = ST_RIGHT;
                    x = QUOTE(117 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class PlayerRankPicture : A3A_Picture
                {
                    idc = A3A_IDC_PLAYERRANKPICTURE;
                    colorText[] = A3A_COLOR_TEXT_DARKER;
                    x = QUOTE(147 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(4 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class AliveLabel : A3A_Text
                {
                    idc = -1;
                    text = "Time alive:"; // TODO UI-update: localize later, not final yet
                    x = QUOTE(98 * GRID_W);
                    y = QUOTE(17 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class AliveText : A3A_Text
                {
                    idc = A3A_IDC_ALIVETEXT;
                    style = ST_RIGHT;
                    text = "";
                    x = QUOTE(130 * GRID_W);
                    y = QUOTE(17 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class MissionsLabel : A3A_Text
                {
                    idc = -1;
                    text = "Missions:"; // TODO UI-update: localize later, not final yet
                    x = QUOTE(98 * GRID_W);
                    y = QUOTE(22 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class MissionsText : A3A_Text
                {
                    idc = A3A_IDC_MISSIONSTEXT;
                    style = ST_RIGHT;
                    text = "";
                    x = QUOTE(130 * GRID_W);
                    y = QUOTE(22 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class KillsLabel : A3A_Text
                {
                    idc = -1;
                    text = "Kills:"; // TODO UI-update: localize later, not final yet
                    x = QUOTE(98 * GRID_W);
                    y = QUOTE(27 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class KillsText : A3A_Text
                {
                    idc = A3A_IDC_KILLSTEXT;
                    style = ST_RIGHT;
                    text = "";
                    x = QUOTE(130 * GRID_W);
                    y = QUOTE(27 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class CommanderBackground : A3A_Background
                {
                    idc = -1;
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(17 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(14 * GRID_H);
                };

                class CommanderPicture : A3A_Picture
                {
                    idc = A3A_IDC_COMMANDERPICTURE;
                    colorText[] = {1,0.9,0.5,1};
                    colorShadow[] = A3A_COLOR_BLACK;
                    shadow = 2;
                    text = A3A_Icon_PlayerCommander;
                    x = QUOTE(79 * GRID_W);
                    y = QUOTE(16 * GRID_H);
                    w = QUOTE(12 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class CommanderText : A3A_Text
                {
                    idc = A3A_IDC_COMMANDERTEXT;
                    style = ST_CENTER;
                    colorText[] = {1,0.9,0.5,1};
                    colorShadow[] = A3A_COLOR_BLACK;
                    shadow = 2;
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(25 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class CommanderButton : A3A_Button
                {
                    idc = A3A_IDC_COMMANDERBUTTON;
                    onButtonClick = "[player, cursorTarget] call A3A_fnc_theBossToggleEligibility; [""update""] call A3A_fnc_playerTab;";
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(34 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class MoneyText : A3A_TextMulti
                {
                    idc = A3A_IDC_MONEYTEXT;
                    text = "";
                    colorBackground[] = {0,0,0,0.5};
                    x = QUOTE(98 * GRID_W);
                    y = QUOTE(34 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class DonateButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_DONATEBUTTON;
                    text = "$STR_antistasi_dialogs_main_donate";
                    onButtonClick = "[""switchTab"", [""donate""]] call A3A_fnc_mainDialog;";
                    x = QUOTE(130 * GRID_W);
                    y = QUOTE(34 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                // Hide top bar checkbox
                class HideTopBarLabel : A3A_Text
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_hide_top_bar";
                    x = QUOTE(98 * GRID_W);
                    y = QUOTE(47 * GRID_H);
                    w = QUOTE(26 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class HideTopBarCheckBox :A3A_CheckBox
                {
                    idc = A3A_IDC_HIDETOPBARCHECKBOX;
                    x = QUOTE(124 * GRID_W);
                    y = QUOTE(47 * GRID_H);
                    w = QUOTE(4 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                // Vehicle section
                class VehicleSectionLabel : A3A_SectionLabelRight
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_vehicles";
                    x = QUOTE(70 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(90 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class NoVehicleGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = A3A_IDC_NOVEHICLEGROUP;
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(64 * GRID_H);
                    w = QUOTE(78 * GRID_W);
                    h = QUOTE(36 * GRID_H);

                    class controls
                    {
                        class NoVehicleText : A3A_Text
                        {
                            idc = A3A_IDC_NOVEHICLETEXT;
                            style = ST_CENTER;
                            text = "$STR_antistasi_dialogs_main_no_vehicle";
                            colorText[] = {0.7,0.7,0.7,1};
                            colorBackground[] = {0,0,0,0.5};
                            x = 0;
                            y = 0;
                            w = QUOTE(78 * GRID_W);
                            h = QUOTE(26 * GRID_H);
                        };
                    };
                };

                class VehicleGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = A3A_IDC_PLAYERVEHICLEGROUP;
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(64 * GRID_H);
                    w = QUOTE(78 * GRID_W);
                    h = QUOTE(36 * GRID_H);

                    class controls
                    {
                        class VehiclePicture : A3A_Picture
                        {
                            idc = A3A_IDC_VEHICLEPICTURE;
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(30 * GRID_W);
                            h = QUOTE(17 * GRID_H);
                        };

                        class VehicleNameBackground : A3A_Background
                        {
                            idc = -1;
                            x = 0;
                            y = QUOTE(17 * GRID_H);
                            w = QUOTE(30 * GRID_W);
                            h = QUOTE(9 * GRID_H);
                        };

                        class VehicleNameLabel : A3A_TextMulti
                        {
                            idc = A3A_IDC_VEHICLENAMELABEL;
                            style = ST_MULTI + ST_CENTER + ST_NO_RECT;
                            x = QUOTE(1 * GRID_W);
                            // Sub-grid position works here because it's only text with transparent background:
                            y = QUOTE(17.5 * GRID_H);
                            w = QUOTE(28 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                        class GarageVehicleButton : A3A_Button
                        {
                            idc = A3A_IDC_GARAGEVEHICLEBUTTON;
                            text = "$STR_antistasi_dialogs_main_garage_vehicle";
                            onButtonClick = "closeDialog 0; _target = cursorObject; if (isNull _target) then { _target = cursorTarget; }; [_target, clientOwner, call HR_GRG_dLock, player] remoteExecCall ['HR_GRG_fnc_addVehicle', 2];";
                            x = QUOTE(32 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(22 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        // TODO UI-update: Vehicle locks/unlocks are no longer a thing outside garage
                        // Either replace this with something else or make the garage button bigger?
                        // class UnlockVehicleButton : A3A_Button
                        // {
                        //   idc = A3A_IDC_UNLOCKVEHICLEBUTTON;
                        //   text = $STR_antistasi_dialogs_main_unlock_vehicle; // Same exists for unlock
                        //   onButtonClick = "hint ""Placeholder\nWill use A3A_fnc_unlockVehicle when merged"""; // TODO UI-update: Replace placeholder when merging
                        //   x = 32 * GRID_W;
                        //   y = 14 * GRID_H;
                        //   w = 22 * GRID_W;
                        //   h = 12 * GRID_H;
                        // };

                        class SellVehicleButton : A3A_Button
                        {
                            idc = A3A_IDC_SELLVEHICLEBUTTON;
                            text = "$STR_antistasi_dialogs_main_sell_vehicle";
                            onButtonClick = "if (player == theBoss) then {closeDialog 0; nul = [player,cursorObject] remoteExecCall [""A3A_fnc_sellVehicle"",2]} else {[""Sell Vehicle"", ""Only the Commander can sell vehicles""] call A3A_fnc_customHint;};"; // TODO UI-update: Move to fn_playerTab.sqf? this shit is loooong
                            x = QUOTE(56 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(22 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class AddToAirSuportButton : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_ADDTOAIRSUPPORTBUTTON;
                            text = "$STR_antistasi_dialogs_main_add_to_air_support";
                            onButtonClick = "closeDialog 0;nul = [cursorObject] call A3A_fnc_addBombRun";
                            x = QUOTE(56 * GRID_W);
                            y = QUOTE(14 * GRID_H);
                            w = QUOTE(22 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };
                    };
                };
                // End of playerTab controlsGroup content
            };
        };

        // Map misbehaves inside controlsGroups, hence this is placed outside
        // See controls.hpp for details
        class CommanderMap : A3A_MapControl
        {
            idc = A3A_IDC_COMMANDERMAP;
            onMouseButtonClick = "[""commanderMapClicked"", [[_this select 2, _this select 3]]] call A3A_fnc_commanderTab";
            x = QUOTE(CENTER_X(DIALOG_W) + 68 * GRID_W);
            y = QUOTE(CENTER_Y(DIALOG_H) + 8 * GRID_H);
            w = QUOTE(84 * GRID_W);
            h = QUOTE(84 * GRID_H);

            // Hide map markers
            showMarkers = 0;

            // Fade satellite texture a bit
            maxSatelliteAlpha = 0.75;
            alphaFadeStartScale = 3.0;
            alphaFadeEndScale = 3.0;

            // Set zoom levels
            scaleMin = 0.05; // 0.2 = Smallest scale showing the 100m grid
            scaleDefault = 0.325; // 0.325 = Largest scale forests still are visible
            scaleMax = 1; // 2 = Max zoom level
        };

        class CommanderTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_COMMANDERTAB;
            // Width set to smaller than usual to avoid an issue where
            // pressing anything other than the map would (invisibly) cover up the
            // map control, making it unclickable
            w = QUOTE(68 * GRID_W);
            show = 0;

            class Controls
            {
                // Main group list
                class MultipleGroupsBackground : A3A_Background
                {
                    idc = A3A_IDC_HCMULTIPLEGROUPSBACKGROUND;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(68 * GRID_H);
                };

                class MultipleGroupsLabel : A3A_SectionLabelRight
                {
                    text = "$STR_antistasi_dialogs_main_hc_groups_label";
                    idc = A3A_IDC_HCMULTIPLEGROUPSLABEL;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class MultipleGroupsView : A3A_ControlsGroupNoHScrollbars
                {
                    idc = A3A_IDC_HCMULTIPLEGROUPSVIEW;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(13 * GRID_H);
                    w = QUOTE(58 * GRID_W);
                    h = QUOTE(63 * GRID_H);

                    class controls {}; // Intentionally empty, controls generated by script
                };

                // Viewing a single group
                class SingleGroupView : A3A_ControlsGroupNoScrollbars
                {
                    idc = A3A_IDC_HCSINGLEGROUPVIEW;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(68 * GRID_H);

                    class controls
                    {
                        class GroupNameLabel : A3A_Button_Left
                        {
                            idc = A3A_IDC_HCGROUPNAME;
                            text = "";
                            onButtonClick = "[""groupNameLabelClicked""] call A3A_fnc_commanderTab";
                            x = 0;
                            y = 0;
                            w = QUOTE(42 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };

                        class FastTravelHCButton : A3A_ShortcutButton
                        {
                            idc = 0; // A3A_IDC_HCFASTTRAVELBUTTON was never defined
                            textureNoShortcut = A3A_Icon_FastTravel;
                            tooltip = "$STR_antistasi_dialogs_main_fast_travel";
                            onButtonClick = "[""groupFastTravelButtonClicked""] call A3A_fnc_commanderTab";
                            x = QUOTE(42 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(6 * GRID_H);

                            class ShortcutPos
                            {
                            	left = 0;
                            	top = 0;
                            	w = QUOTE(6 * GRID_W);
                            	h = QUOTE(6 * GRID_H);
                            };
                        };

                        class RemoteControlHCButton : A3A_ShortcutButton
                        {
                            idc = -1;
                            textureNoShortcut = A3A_Icon_Remotecontrol;
                            tooltip = "$STR_antistasi_dialogs_main_remote_control_tooltip";
                            onButtonClick = "[""groupRemoteControlButtonClicked""] call A3A_fnc_commanderTab";
                            x = QUOTE(48 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(6 * GRID_H);

                            class ShortcutPos
                            {
                            	left = 0;
                            	top = 0;
                            	w = QUOTE(6 * GRID_W);
                            	h = QUOTE(6 * GRID_H);
                            };
                        };

                        class GroupBackground : A3A_Background
                        {
                            idc = -1;
                            x = 0;
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(54 * GRID_W);
                            h = QUOTE(62 * GRID_H);
                        };

                        class IconsControlsGroup : A3A_ControlsGroupNoScrollbars
                        {
                            idc = A3A_IDC_HCGROUPSTATUSICONS;
                            x = QUOTE(22 * GRID_W);
                            y = QUOTE(8 * GRID_H);
                            w = QUOTE(30 * GRID_W);
                            h = QUOTE(6 * GRID_H);

                            class controls {}; // Intentionally empty, controls generated by script
                        };

                        class GroupUnitCountIcon : A3A_Picture
                        {
                            idc = -1;
                            text = A3A_Icon_GroupUnitCount;
                            tooltip = "$STR_antistasi_dialogs_main_hc_unit_count_tooltip";
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(8 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GroupUnitCountText : A3A_Text
                        {
                            idc = A3A_IDC_HCGROUPCOUNT;
                            text = "10 / 10";
                            tooltip = "$STR_antistasi_dialogs_main_hc_unit_count_tooltip";
                            x = QUOTE(6 * GRID_W);
                            y = QUOTE(8 * GRID_H);
                            w = QUOTE(16 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GroupCombatModeLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_combat_mode";
                            x = 0;
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GroupCombatModeText : A3A_Text
                        {
                            idc = A3A_IDC_HCGROUPCOMBATMODE;
                            style = ST_RIGHT;
                            text = "";
                            x = QUOTE(28 * GRID_W);
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GroupVehicleLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_vehicle";
                            x = 0;
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GroupVehicleText : A3A_StructuredText
                        {
                            idc = A3A_IDC_HCGROUPVEHICLE;
                            // style = ST_RIGHT + ST_MULTI;
                            x = QUOTE(28 * GRID_W);
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };


                        class FireMissionButton : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_HCFIREMISSIONBUTTON;
                            text = "$STR_antistasi_dialogs_main_hc_fire_mission_button";
                            onButtonClick = "[""updateFireMissionView""] call A3A_fnc_commanderTab;";
                            x = QUOTE(28 * GRID_W);
                            y = QUOTE(30 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                        class MountButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_mount"; // TODO UI-update: update on mount status
                            x = QUOTE(2 * GRID_H);
                            y = QUOTE(40 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class AddVehicleButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_add_vehicle";
                            x = QUOTE(2 * GRID_H);
                            y = QUOTE(54 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class GarrisonButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_garrison";
                            x = QUOTE(28 * GRID_W);
                            y = QUOTE(40 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class DismissButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_dismiss";
                            onButtonClick = "[""groupDismissButtonClicked""] call A3A_fnc_commanderTab";
                            x = QUOTE(28 * GRID_W);
                            y = QUOTE(54 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };
                    }; // End of SingleGroupView controls
                };


                // Fire mission view
                class FireMissionControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = A3A_IDC_FIREMISSONCONTROLSGROUP;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(68 * GRID_H);

                    class controls
                    {
                        // Label also works as a back button
                        class FireMissionLabel : A3A_Button_Left
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_fire_mission_label";
                            onButtonClick = "[""update""] call A3A_fnc_commanderTab;";
                            x = 0;
                            y = 0;
                            w = QUOTE(54 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };

                        class FireMissionBackground : A3A_Background
                        {
                            idc = -1;
                            x = 0;
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(54 * GRID_W);
                            h = QUOTE(62 * GRID_H);
                        };

                        class AmmoLabel : A3A_SectionLabelRight
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_fire_mission_ammo";
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(8 * GRID_H);
                            w = QUOTE(50 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class HeRoundsCountLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_fire_mission_ammo_he";
                            colorBackground[] = A3A_COLOR_BACKGROUND;
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(13 * GRID_H);
                            w = QUOTE(25 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class HeRoundsCountText : A3A_Text
                        {
                            idc = A3A_IDC_HEROUNDSTEXT;
                            text = "0";
                            colorBackground[] = A3A_COLOR_BACKGROUND;
                            style = ST_RIGHT;
                            x = QUOTE(27 * GRID_W);
                            y = QUOTE(13 * GRID_H);
                            w = QUOTE(25 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class SmokeRoundsCountLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_hc_fire_mission_ammo_smoke";
                            colorBackground[] = A3A_COLOR_BACKGROUND;
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(18 * GRID_H);
                            w = QUOTE(25 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class SmokeRoundsCountText : A3A_Text
                        {
                            idc = A3A_IDC_SMOKEROUNDSTEXT;
                            text = "0";
                            colorBackground[] = A3A_COLOR_BACKGROUND;
                            style = ST_RIGHT;
                            x = QUOTE(27 * GRID_W);
                            y = QUOTE(18 * GRID_H);
                            w = QUOTE(25 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ShellTypeControlsGroup : A3A_ControlsGroupNoScrollbars
                        {
                            idc = -1;
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(27 * GRID_H);
                            w = QUOTE(50 * GRID_W);
                            h = QUOTE(4 * GRID_H);

                            class controls
                            {
                                class ShellTypeLabel : A3A_Text
                                {
                                    idc = -1;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_shell_type_label";
                                    colorBackground[] = A3A_COLOR_BACKGROUND;
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(20 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class HeButton : A3A_Button
                                {
                                    idc = A3A_IDC_HEBUTTON;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_shell_type_he";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""he""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(20 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(15 * GRID_W);
                                    h = QUOTE(4 * GRID_H);

                                    // Colors are a bit different on these because we use them as radio buttons
                                    // We disable them to show that they are active
                                    colorDisabled[] = A3A_COLOR_BUTTON_TEXT;
                                    colorBackgroundDisabled[] = A3A_COLOR_BUTTON_ACTIVE;
                                };

                                class SmokeButton : A3A_Button
                                {
                                    idc = A3A_IDC_SMOKEBUTTON;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_shell_type_smoke";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""smoke""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(35 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(15 * GRID_W);
                                    h = QUOTE(4 * GRID_H);

                                    // Colors, see HE button for clarification
                                    colorDisabled[] = A3A_COLOR_BUTTON_TEXT;
                                    colorBackgroundDisabled[] = A3A_COLOR_BUTTON_ACTIVE;
                                };
                            };
                        };

                        class MissionTypeControlsGroup : A3A_ControlsGroupNoScrollbars
                        {
                            idc = -1;
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(32 * GRID_H);
                            w = QUOTE(50 * GRID_W);
                            h = QUOTE(4 * GRID_H);

                            class controls
                            {
                                class MissionTypeLabel : A3A_Text
                                {
                                    idc = -1;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_type_label";
                                    colorBackground[] = A3A_COLOR_BACKGROUND;
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(20 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class PointStrikeButton : A3A_Button
                                {
                                    idc = A3A_IDC_POINTSTRIKEBUTTON;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_type_point";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""point""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(20 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(15 * GRID_W);
                                    h = QUOTE(4 * GRID_H);

                                    // Colors, see HE button for clarification
                                    colorDisabled[] = A3A_COLOR_BUTTON_TEXT;
                                    colorBackgroundDisabled[] = A3A_COLOR_BUTTON_ACTIVE;
                                };

                                class BarrageButton : A3A_Button
                                {
                                    idc = A3A_IDC_BARRAGEBUTTON;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_type_barrage";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""barrage""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(35 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(15 * GRID_W);
                                    h = QUOTE(4 * GRID_H);

                                    // Colors, see HE button for clarification
                                    colorDisabled[] = A3A_COLOR_BUTTON_TEXT;
                                    colorBackgroundDisabled[] = A3A_COLOR_BUTTON_ACTIVE;
                                };
                            };
                        };

                        class RoundsControlsGroup : A3A_ControlsGroupNoScrollbars
                        {
                            idc = A3A_IDC_ROUNDSCONTROLSGROUP;
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(37 * GRID_H);
                            w = QUOTE(50 * GRID_W);
                            h = QUOTE(4 * GRID_H);

                            class controls
                            {
                                class RoundsLabel : A3A_Text
                                {
                                    idc = -1;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_rounds_label";
                                    colorBackground[] = A3A_COLOR_BACKGROUND;
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(20 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class RoundsEditbox : A3A_Edit
                                {
                                    idc = A3A_IDC_ROUNDSEDITBOX;
                                    text = "0";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    style = ST_RIGHT + ST_NO_RECT;
                                    onLoad = "_this#0 ctrlEnable false";
                                    colorDisabled[] = A3A_COLOR_TEXT;
                                    colorBackground[] = A3A_COLOR_BLACK;
                                    x = QUOTE(20 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(22 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class AddRoundsButton : A3A_Button
                                {
                                    idc = A3A_IDC_ADDROUNDSBUTTON;
                                    text = "+";
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""addround""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(42 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(4 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class SubRoundsButton : A3A_Button
                                {
                                    idc = A3A_IDC_SUBROUNDSBUTTON;
                                    text = "-";
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""subround""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(46 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(4 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };
                            };
                        };

                        class StartPositionControlsGroup : A3A_ControlsGroupNoScrollbars
                        {
                            idc = A3A_IDC_STARTPOSITIONCONTROLSGROUP;
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(42 * GRID_H);
                            w = QUOTE(50 * GRID_W);
                            h = QUOTE(4 * GRID_H);

                            class controls
                            {
                                class StartPositionLabel : A3A_Text
                                {
                                    idc = A3A_IDC_STARTPOSITIONLABEL;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_position_label";
                                    colorBackground[] = A3A_COLOR_BACKGROUND;
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(20 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class StartPositionEditbox : A3A_Edit
                                {
                                    idc = A3A_IDC_STARTPOSITIONEDITBOX;
                                    text = "";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    style = ST_RIGHT + ST_NO_RECT;
                                    onLoad = "_this#0 ctrlEnable false";
                                    colorDisabled[] = A3A_COLOR_TEXT;
                                    colorBackground[] = A3A_COLOR_BLACK;
                                    x = QUOTE(20 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(22 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class SetStartPositionButton : A3A_Button
                                {
                                    idc = -1;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_set";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""setstart""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(42 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(8 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };
                            };
                        };

                        class EndPositionControlsGroup : A3A_ControlsGroupNoScrollbars
                        {
                            idc = A3A_IDC_ENDPOSITIONCONTROLSGROUP;
                            x = QUOTE(2 * GRID_W);
                            y = QUOTE(47 * GRID_H);
                            w = QUOTE(50 * GRID_W);
                            h = QUOTE(4 * GRID_H);

                            class controls
                            {
                                class EndPositionLabel : A3A_Text
                                {
                                    idc = A3A_IDC_ENDPOSITIONLABEL;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_position_end_label";
                                    colorBackground[] = A3A_COLOR_BACKGROUND;
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(20 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class EndPositionEditbox : A3A_Edit
                                {
                                    idc = A3A_IDC_ENDPOSITIONEDITBOX;
                                    text = "";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    style = ST_RIGHT + ST_NO_RECT;
                                    onLoad = "_this#0 ctrlEnable false";
                                    colorDisabled[] = A3A_COLOR_TEXT;
                                    colorBackground[] = A3A_COLOR_BLACK;
                                    x = QUOTE(20 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(22 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class SetEndPositionButton : A3A_Button
                                {
                                    idc = -1;
                                    text = "$STR_antistasi_dialogs_main_hc_fire_mission_set";
                                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                                    onButtonClick = "[""fireMissionSelectionChanged"",[""setend""]] call A3A_fnc_commanderTab;";
                                    x = QUOTE(42 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(8 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };
                            };
                        };

                        class FireButton : A3A_Button
                        {
                            idc = A3A_IDC_FIREBUTTON;
                            text = "$STR_antistasi_dialogs_main_hc_fire_mission_fire_button";
                            onbuttonClick = "[""fireMissionButtonClicked""] call A3A_fnc_commanderTab";
                            x = QUOTE(17 * GRID_W);
                            y = QUOTE(56 * GRID_H);
                            w = QUOTE(20 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                    };
                };

                class NoRadioControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = A3A_IDC_NORADIOCONTROLSGROUP;
                    colorBackground[] = A3A_COLOR_BACKGROUND;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(68 * GRID_H);

                    class controls
                    {
                        class NoRadioBackground : A3A_Background
                        {
                            idc = -1;
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(54 * GRID_W);
                            h = QUOTE(68 * GRID_H);
                        };

                        class NoRadioIcon : A3A_Picture
                        {
                            idc = -1;
                            text = A3A_Icon_AT_Minefield;
                            colorText[] = A3A_COLOR_BUTTON_BACKGROUND_DISABLED;
                            x = QUOTE(15 * GRID_W);
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(24 * GRID_H);
                        };

                        class NoRadioText : A3A_Text
                        {
                            idc = -1;
                            style = ST_CENTER;
                            text = "$STR_antistasi_dialogs_main_commander_no_radio";
                            colorText[] = A3A_COLOR_BUTTON_BACKGROUND_DISABLED;
                            sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(39 * GRID_H);
                            w = QUOTE(54 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };
                    };
                };


                // Bottom buttons

                class AirSupportButton : A3A_Button
                {
                    idc = A3A_IDC_AIRSUPPORTBUTTON;
                    text = "$STR_antistasi_dialogs_main_air_support_button";
                    onButtonClick = "[""switchTab"", [""airsupport""]] call A3A_fnc_mainDialog;";
                    x = QUOTE(10 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(24 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class GarbageCleanButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_GARBAGECLEANBUTTON;
                    text = "$STR_antistasi_dialogs_main_garbage_clean_button";
                    onButtonclick = "[""showGarbageCleanOptions""] call A3A_fnc_commanderTab";
                    x = QUOTE(36 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(24 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class GarbageCleanControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = A3A_IDC_GARBAGECLEANCONTROLSGROUP;
                    x = QUOTE(10 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(50 * GRID_W);
                    h = QUOTE(12 * GRID_H);

                    class controls
                    {
                        class GarbageCleanMapButton : A3A_ShortcutButton
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_garbage_clean_all";
                            onButtonClick = "[""garbageCleanMapButtonClicked""] call A3A_fnc_commanderTab";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class GarbageCleanHQButton : A3A_ShortcutButton
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_main_garbage_clean_hq";
                            onButtonClick = "[""garbageCleanHqButtonClicked""] call A3A_fnc_commanderTab";
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(24 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                    };
                };

            };
        };

        class AdminTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_ADMINTAB;
            show = 0;

            class Controls
            {
                class DebugSectionLabel : A3A_SectionLabelRight
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_debug_info_label";
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(48 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class DebugInfoText : A3A_StructuredText
                {
                    idc = A3A_IDC_DEBUGINFO;
                    colorBackground[] = A3A_COLOR_BACKGROUND;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(12 * GRID_H);
                    w = QUOTE(48 * GRID_W);
                    h = QUOTE(44 * GRID_H);
                };

                class PlayerManagementButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_PLAYERMANAGEMENTBUTTON;
                    text = "$STR_antistasi_dialogs_main_admin_player_management_button";
                    onButtonClick = "[""switchTab"", [""playermanagement""]] call A3A_fnc_mainDialog;";
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(64 * GRID_H);
                    w = QUOTE(48 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                    size = QUOTE(GUI_TEXT_SIZE_LARGE);

                    class TextPos
                    {
                        left = QUOTE(2 * GRID_W);
                        right = QUOTE(2 * GRID_H);
                        top = QUOTE(3 * GRID_W);
                        bottom = QUOTE(3 * GRID_H);
                    };
                };

                class ResetHqButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_RESETHQBUTTON;
                    text = "$STR_antistasi_dialogs_main_admin_reset_hq_button";
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(48 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                    size = QUOTE(GUI_TEXT_SIZE_LARGE);

                    class TextPos
                    {
                        left = QUOTE(2 * GRID_W);
                        right = QUOTE(2 * GRID_H);
                        top = QUOTE(3 * GRID_W);
                        bottom = QUOTE(3 * GRID_H);
                    };
                };

                class AiSectionLabel : A3A_SectionLabelRight
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_ai_options_label";
                    x = QUOTE(70 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(90 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class CivLimitLabel : A3A_Text
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_civ_limit_label";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_MEDIUM);
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(16 * GRID_H);
                    w = QUOTE(24 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class CivLimitSlider : A3A_Slider
                {
                    idc = A3A_IDC_CIVLIMITSLIDER;
                    x = QUOTE(98 * GRID_W);
                    y = QUOTE(16 * GRID_H);
                    w = QUOTE(40 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                    onSliderPosChanged = "[""civLimitSliderChanged""] spawn A3A_fnc_adminTab";
                };

                class SpawnDistanceLabel : A3A_Text
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_spawn_distance_label";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_MEDIUM);
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(22 * GRID_H);
                    w = QUOTE(24 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class SpawnDistanceSlider : A3A_Slider
                {
                    idc = A3A_IDC_SPAWNDISTANCESLIDER;
                    x = QUOTE(98 * GRID_W);
                    y = QUOTE(22 * GRID_H);
                    w = QUOTE(40 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                    onSliderPosChanged = "[""spawnDistanceSliderChanged""] spawn A3A_fnc_adminTab";
                };

                class SpawnDistanceEditBox : A3A_Edit
                {
                    idc = A3A_IDC_SPAWNDISTANCEEDITBOX;
                    style = ST_RIGHT;
                    text = "0";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_MEDIUM);
                    x = QUOTE(140 * GRID_W);
                    y = QUOTE(22 * GRID_H);
                    w = QUOTE(12 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                    onChar = "[""spawnDistanceEditBoxChanged""] spawn A3A_fnc_adminTab";
                };

                class AiSectionWarningBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.6};
                    x = QUOTE(75 * GRID_W);
                    y = QUOTE(37 * GRID_H);
                    w = QUOTE(52 * GRID_W);
                    h = QUOTE(10 * GRID_H);
                };

                class AiSectionWarningIcon : A3A_Picture
                {
                    idc = -1;
                    text = A3A_Icon_Warning;
                    colorText[] = A3A_COLOR_ERROR;
                    x = QUOTE(76 * GRID_W);
                    y = QUOTE(38 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class AiSectionWarning : A3A_TextMulti
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_ai_section_warning";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                    font = "PuristaLight";
                    x = QUOTE(85 * GRID_W);
                    y = QUOTE(37 * GRID_H);
                    w = QUOTE(42 * GRID_W);
                    h = QUOTE(10 * GRID_H);
                };

                class CommitAiButton : A3A_Button
                {
                    idc = A3A_IDC_COMMITAIBUTTON;
                    text = "$STR_antistasi_dialogs_main_admin_ai_commit_button";
                    onButtonClick = "[""confirmAILimit""] call A3A_fnc_adminTab;"; // TODO UI-update: Placeholder
                    x = QUOTE(132 * GRID_W);
                    y = QUOTE(36 * GRID_H);
                    w = QUOTE(20 * GRID_W);
                    h = QUOTE(12 * GRID_H);

                    class TextPos
                    {
                        left = QUOTE(2 * GRID_W);
                        right = QUOTE(2 * GRID_W);
                        top = QUOTE(1 * GRID_H);
                        bottom = QUOTE(1 * GRID_W);
                    };
                };

                class TpSectionLabel : A3A_SectionLabelRight
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_label";
                    x = QUOTE(70 * GRID_W);
                    y = QUOTE(56 * GRID_H);
                    w = QUOTE(90 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class TpPetrosButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_petros_button";
                    onButtonClick = "petros setPos (player modelToWorld [0,2,0]);";
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(64 * GRID_H);
                    w = QUOTE(16 * GRID_H);
                    h = QUOTE(12 * GRID_H);
                };

                class TpArsenalBoxButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_arsenal_box_button";
                    onButtonClick = "boxX setPos (player modelToWorld [0,2,0]);";
                    x = QUOTE(103 * GRID_W);
                    y = QUOTE(64 * GRID_H);
                    w = QUOTE(16 * GRID_H);
                    h = QUOTE(12 * GRID_H);
                };

                class TpVehicleBoxButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_vehicle_box_button";
                    onButtonClick = "vehicleBox setPos (player modelToWorld [0,2,0]);";
                    x = QUOTE(132 * GRID_W);
                    y = QUOTE(64 * GRID_H);
                    w = QUOTE(16 * GRID_H);
                    h = QUOTE(12 * GRID_H);
                };

                class TpFlagButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_flag_button";
                    onButtonClick = "flagX setPos (player modelToWorld [0,2,0]);";
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(16 * GRID_H);
                    h = QUOTE(12 * GRID_H);
                };

                class TpMapButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_map_button";
                    onButtonClick = "mapX setPos (player modelToWorld [0,2,0]);";
                    x = QUOTE(132 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(16 * GRID_H);
                    h = QUOTE(12 * GRID_H);
                };
            };
        };


        /////////////
        // SUBTABS //
        /////////////

        class FastTravelMap : A3A_MapControl
        {
            idc = A3A_IDC_FASTTRAVELMAP;
            onMouseButtonClick = "[""mapClicked"", [[_this select 2, _this select 3]]] call A3A_fnc_fastTravelTab";
            x = QUOTE(CENTER_X(DIALOG_W) + 48 * GRID_W);
            y = QUOTE(CENTER_Y(DIALOG_H) + 8 * GRID_H);
            w = QUOTE(104 * GRID_W);
            h = QUOTE(84 * GRID_H);

            // Hide map markers
            showMarkers = 0;

            // Fade satellite texture a bit
            maxSatelliteAlpha = 0.75;
            alphaFadeStartScale = 3.0;
            alphaFadeEndScale = 3.0;

            // Set zoom levels
            scaleMin = 0.2; // 0.2 = Smallest scale showing the 100m grid
            scaleDefault = 0.325; // 0.325 = Largest scale forests still are visible
            scaleMax = 1; // 2 = Max zoom level
        };

        class FastTravelTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_FASTTRAVELTAB;
            // Width set to smaller than usual to avoid an issue where
            // pressing anything other than the map would (invisibly) cover up the
            // map control, making it unclickable
            w = QUOTE(44 * GRID_W);
            show = 0;

            class controls
            {

                class FastTravelLabel : A3A_SectionLabelRight
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_fast_travel";
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class FastTravelBackground : A3A_Background
                {
                    idc = -1;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(12 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(68 * GRID_H);
                };

                class FastTravelSelectText : A3A_TextMulti
                {
                    idc = A3A_IDC_FASTTRAVELSELECTTEXT;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(14 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(16 * GRID_H);
                };

                class FastTravelInfoText : A3A_StructuredText
                {
                    idc = A3A_IDC_FASTTRAVELLOCATIONGROUP;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(14 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(60 * GRID_H);
                };

                class FastTravelCommitButton : A3A_Button
                {
                    idc = A3A_IDC_FASTTRAVELCOMMITBUTTON;
                    text = "$STR_antistasi_dialogs_main_fast_travel";
                    // tooltip = $STR_antistasi_dialogs_main_fast_travel_tooltip;
                    onButtonClick = "[""commitButtonClicked""] call A3A_fnc_fastTravelTab;";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };
            };
        };

        class ConstructTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_CONSTRUCTTAB;
            show = 0;

            class controls
            {
                class ConstructControlsGroup : A3A_ControlsGroupNoHScrollbars
                {
                    idc = A3A_IDC_CONSTRUCTGROUP;
                    x = 0;
                    y = QUOTE(4 * GRID_H);
                    w = QUOTE(PX_W(DIALOG_W));
                    h = QUOTE(PX_H(DIALOG_H) - 8 * GRID_H);
                };
            };
        };

        class AIManagementTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_AIMANAGEMENTTAB;
            show = 0;

            class controls
            {

                class AIListLabel : A3A_SectionLabelRight
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_ai_management_ai_list_label";
                    x = QUOTE(15 * GRID_W);
                    y = QUOTE(14 * GRID_H);
                    w = QUOTE(68 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class ClearAIListSelectionButton : A3A_Button
                {
                    idc = -1;
                    sizeEx = QUOTE(GUI_TEXT_SIZE_SMALL);
                    text = "$STR_antistasi_dialogs_main_ai_management_clear_button";
                    tooltip = "$STR_antistasi_dialogs_main_ai_management_clear_tooltip";
                    onButtonClick = "[""clearAIListboxSelection""] call A3A_fnc_aiManagementTab;";
                    x = QUOTE(83 * GRID_W);
                    y = QUOTE(14 * GRID_H);
                    w = QUOTE(10 * GRID_W);
                    h = QUOTE(4 * GRID_H);
                };

                class AIListBox : A3A_ListboxMulti
                {
                    idc = A3A_IDC_AILISTBOX;
                    onLBSelChanged = "[""aiListBoxSelectionChanged""] spawn A3A_fnc_aiManagementTab";
                    x = QUOTE(15 * GRID_W);
                    y = QUOTE(18 * GRID_H);
                    w = QUOTE(78 * GRID_W);
                    h = QUOTE(68 * GRID_H);
                };

                class AIButtonsControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = -1;
                    x = QUOTE(101 * GRID_W);
                    y = QUOTE(14 * GRID_H);
                    w = QUOTE(44 * GRID_W);
                    h = QUOTE(72 * GRID_H);

                    class controls
                    {
                        class AiControlButton : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_AICONTROLBUTTON;
                            text = "$STR_antistasi_dialogs_main_ai_management_temp_ai_control_button";
                            onButtonClick = "[""aiControlButtonClicked""] call A3A_fnc_aiManagementTab";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(32 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class AiControlIcon : A3A_Picture
                        {
                            idc = A3A_IDC_AICONTROLICON;
                            text = A3A_Icon_Remotecontrol;
                            x = QUOTE(36 * GRID_W);
                            y = QUOTE(2 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                        class DismissButton : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_AIDISMISSBUTTON;
                            text = "$STR_antistasi_dialogs_main_ai_management_dismiss_button";
                            onButtonClick = "[""dismissButtonClicked""] call A3A_fnc_aiManagementTab";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(32 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class DismissIcon : A3A_Picture
                        {
                            idc = A3A_IDC_AIDISMISSICON;
                            text = A3A_Icon_Dismiss;
                            x = QUOTE(36 * GRID_W);
                            y = QUOTE(22 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                        class AutoLootButton : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_AIAUTOLOOTBUTTON;
                            text = "$STR_antistasi_dialogs_main_ai_management_auto_rearm_button";
                            onButtonClick = "[""autoLootButtonClicked""] call A3A_fnc_aiManagementTab";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(40 * GRID_H);
                            w = QUOTE(32 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class AutoLootIcon : A3A_Picture
                        {
                            idc = A3A_IDC_AIAUTOLOOTICON;
                            text = A3A_Icon_Rearm;
                            x = QUOTE(36 * GRID_W);
                            y = QUOTE(42 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                        class AutoHealButton : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_AIAUTOHEALBUTTON;
                            text = "$STR_antistasi_dialogs_main_ai_management_auto_heal_button";
                            onButtonClick = "[""autoHealButtonClicked""] call A3A_fnc_aiManagementTab";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(60 * GRID_H);
                            w = QUOTE(32 * GRID_W);
                            h = QUOTE(12 * GRID_H);
                        };

                        class AutoHealIcon : A3A_Picture
                        {
                            idc = A3A_IDC_AIAUTOHEALICON;
                            text = A3A_Icon_Heal;
                            x = QUOTE(36 * GRID_W);
                            y = QUOTE(62 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };
                    };
                };

            };
        };

        class DonateTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_DONATETAB;
            show = 0;

            class controls
            {

                class PlayerList : A3A_Listbox
                {
                    idc = A3A_IDC_DONATEPLAYERLIST;
                    x = QUOTE(8 * GRID_H);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(84 * GRID_H);
                };

                class MoneyLabel : A3A_Text
                {
                    idc = -1;
                    style = ST_LEFT;
                    text = "$STR_antistasi_dialogs_main_current_money";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(83 * GRID_W);
                    y = QUOTE(30 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class MoneyText : A3A_Text
                {
                    idc = A3A_IDC_DONATIONMONEYTEXT;
                    style = ST_RIGHT;
                    text = "€ 0";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(113 * GRID_W);
                    y = QUOTE(30 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class DonationLabel : A3A_Text
                {
                    idc = -1;
                    style = ST_LEFT;
                    text = "$STR_antistasi_dialogs_main_donate_label";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(83 * GRID_W);
                    y = QUOTE(40 * GRID_H);
                    w = QUOTE(30 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class MoneyEditBox : A3A_Edit
                {
                    idc = A3A_IDC_MONEYEDITBOX;
                    style = ST_RIGHT;
                    text = "0";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(123 * GRID_W);
                    y = QUOTE(40 * GRID_H);
                    w = QUOTE(16 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                    onChar = "[""moneyEditBoxChanged""] spawn A3A_fnc_donateTab";
                };

                class EuroLabel : A3A_Text
                {
                    idc = -1;
                    style = ST_RIGHT;
                    text = "€";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(139 * GRID_W);
                    y = QUOTE(40 * GRID_H);
                    w = QUOTE(4 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class Sub1000Button : A3A_ShortcutButton
                {
                    idc = -1;
                    textureNoShortcut = A3A_ArrowEmpty_3L;
                    onButtonClick = "[""donationAdd"", [-1000]] spawn A3A_fnc_donateTab";
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(6 * GRID_W);
                    h = QUOTE(6 * GRID_H);

                    class ShortcutPos
                    {
                        left = 0;
                        top = 0;
                        w = QUOTE(6 * GRID_W);
                        h = QUOTE(6 * GRID_H);
                    };
                };

                class Sub100Button : A3A_ShortcutButton
                {
                    idc = -1;
                    textureNoShortcut = A3A_ArrowEmpty_2L;
                    onButtonClick = "[""donationAdd"", [-100]] spawn A3A_fnc_donateTab";
                    x = QUOTE(81 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(6 * GRID_W);
                    h = QUOTE(6 * GRID_H);

                    class ShortcutPos
                    {
                        left = 0;
                        top = 0;
                        w = QUOTE(6 * GRID_W);
                        h = QUOTE(6 * GRID_H);
                    };
                };

                class MoneySlider : A3A_Slider
                {
                    idc = A3A_IDC_MONEYSLIDER;
                    color[] = {1,1,1,1};
                    arrowEmpty = A3A_ArrowEmpty_1L;
                    arrowFull = A3A_ArrowFull_1L;
                    x = QUOTE(88 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(50 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                    onSliderPosChanged = "[""moneySliderChanged""] spawn A3A_fnc_donateTab";
                };

                class Add100Button : A3A_ShortcutButton
                {
                    idc = -1;
                    textureNoShortcut = A3A_ArrowEmpty_2R;
                    onButtonClick = "[""donationAdd"", [100]] spawn A3A_fnc_donateTab";
                    x = QUOTE(139 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(6 * GRID_W);
                    h = QUOTE(6 * GRID_H);

                    class ShortcutPos
                    {
                        left = 0;
                        top = 0;
                        w = QUOTE(6 * GRID_W);
                        h = QUOTE(6 * GRID_H);
                    };
                };

                class Add1000Button : A3A_ShortcutButton
                {
                    idc = -1;
                    textureNoShortcut = A3A_ArrowEmpty_3R;
                    onButtonClick = "[""donationAdd"", [1000]] spawn A3A_fnc_donateTab";
                    x = QUOTE(146 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(6 * GRID_W);
                    h = QUOTE(6 * GRID_H);

                    class ShortcutPos
                    {
                        left = 0;
                        top = 0;
                        w = QUOTE(6 * GRID_W);
                        h = QUOTE(6 * GRID_H);
                    };
                };

                class DonatePlayerButton : A3A_Button
                {
                    idc = A3A_IDC_DONATEPLAYERBUTTON;
                    text = "$STR_antistasi_dialogs_main_donate_player";
                    onButtonClick = "hint ""Placeholder\nWill use A3A_fnc_donateMoney when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(74 * GRID_W);
                    y = QUOTE(63 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(10 * GRID_H);
                };

                class DonateFactionButton : A3A_Button
                {
                    idc = A3A_IDC_DONATEFACTIONBUTTON;
                    text = "$STR_antistasi_dialogs_main_donate_faction";
                    onButtonClick = "hint ""Placeholder\nWill use A3A_fnc_donateMoney when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(116 * GRID_W);
                    y = QUOTE(63 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(10 * GRID_H);
                };
            };
        };

        class AirSupportTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_AIRSUPPORTTAB;
            show = 0;

            class controls
            {
                class AirSupportInfoBackground : A3A_Background
                {
                    idc = -1;
                    x = QUOTE(38 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(84 * GRID_W);
                    h = QUOTE(38 * GRID_H);
                };

                class RemainingPointsLabel : A3A_Text
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_air_support_remaining_points";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(40 * GRID_W);
                    y = QUOTE(10 * GRID_H);
                    w = QUOTE(60 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class RemainingPointsText : A3A_Text
                {
                    idc = A3A_IDC_AIRSUPPORTPOINTSTEXT;
                    style = ST_RIGHT;
                    text = "0";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(100 * GRID_W);
                    y = QUOTE(10 * GRID_H);
                    w = QUOTE(20 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class AirSupportAircraftLabel : A3A_Text
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_air_support_aircraft_used";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(40 * GRID_W);
                    y = QUOTE(18 * GRID_H);
                    w = QUOTE(40 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class AirSupportAircraftText : A3A_Text
                {
                    idc = A3A_IDC_AIRSUPPORTAIRCRAFTTEXT;
                    text = "Antonov An-2";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    style = ST_RIGHT;
                    x = QUOTE(80 * GRID_W);
                    y = QUOTE(18 * GRID_H);
                    w = QUOTE(40 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class AirSupportInfoText : A3A_TextMulti
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_air_support_info";
                    colorText[] = A3A_COLOR_TEXT_DARKER;
                    x = QUOTE(44 * GRID_W);
                    y = QUOTE(28 * GRID_H);
                    w = QUOTE(72 * GRID_W);
                    h = QUOTE(14 * GRID_H);
                };

                class HeBombsIcon : A3A_Picture
                {
                    idc = A3A_IDC_AIRSUPPORTHEICON;
                    text = A3A_Icon_HE_Bombs;
                    x = QUOTE(24 * GRID_W);
                    y = QUOTE(54 * GRID_H);
                    w = QUOTE(16 * GRID_W);
                    h = QUOTE(16 * GRID_H);
                };

                class HeBombsButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_AIRSUPPORTHEBUTTON;
                    text = "$STR_antistasi_dialogs_main_air_support_he_bombs";
                    onButtonClick = "closeDialog 0;[""HE""] spawn A3A_fnc_NATObomb;";
                    x = QUOTE(16 * GRID_W);
                    y = QUOTE(74 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class CarpetBombingIcon : A3A_Picture
                {
                    idc = A3A_IDC_AIRSUPPORTCARPETICON;
                    text = A3A_Icon_Carpet_Bombing;
                    x = QUOTE(72 * GRID_W);
                    y = QUOTE(54 * GRID_H);
                    w = QUOTE(16 * GRID_W);
                    h = QUOTE(16 * GRID_H);
                };

                class CarpetBombingButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_AIRSUPPORTCARPETBUTTON;
                    text = "$STR_antistasi_dialogs_main_air_support_carpet_bombing";
                    onButtonClick = "closeDialog 0;[""CLUSTER""] spawn A3A_fnc_NATObomb;";
                    x = QUOTE(64 * GRID_W);
                    y = QUOTE(74 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class NapalmBombIcon : A3A_Picture
                {
                    idc = A3A_IDC_AIRSUPPORTNAPALMICON;
                    text = A3A_Icon_Napalm_Bomb;
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(54 * GRID_H);
                    w = QUOTE(16 * GRID_W);
                    h = QUOTE(16 * GRID_H);
                };

                class NapalmBombButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_AIRSUPPORTNAPALMBUTTON;
                    text = "$STR_antistasi_dialogs_main_air_support_napalm";
                    onButtonClick = "closeDialog 0;[""NAPALM""] spawn A3A_fnc_NATObomb;";
                    x = QUOTE(112 * GRID_W);
                    y = QUOTE(74 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };
            };
        };

        class PlayerManagementTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_PLAYERMANAGEMENTTAB;
            show = 0;

            class controls
            {

                class PlayerListBackground : A3A_Background
                {
                    idc = -1;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(12 * GRID_H);
                    w = QUOTE(106 * GRID_W);
                    h = QUOTE(82 * GRID_H);
                };

                class NameLabel : A3A_Text
                {
                    text = "$STR_antistasi_dialogs_main_admin_player_name_label";
                    x = QUOTE(9 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(16 * GRID_W);
                    h = QUOTE(4 * GRID_W);
                    sizeEx = QUOTE(GUI_TEXT_SIZE_MEDIUM);
                };

                class DistanceLabel : A3A_Text
                {
                    text = "$STR_antistasi_dialogs_main_admin_player_distance_label";
                    x = QUOTE(71 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(16 * GRID_W);
                    h = QUOTE(4 * GRID_W);
                    sizeEx = QUOTE(GUI_TEXT_SIZE_MEDIUM);
                };

                class UIDLabel : A3A_Text
                {
                    text = "$STR_antistasi_dialogs_main_admin_player_uid_label";
                    x = QUOTE(85 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(16 * GRID_W);
                    h = QUOTE(4 * GRID_W);
                    sizeEx = QUOTE(GUI_TEXT_SIZE_MEDIUM);
                };

                class PlayerList : A3A_ListNBox
                {
                    idc = A3A_IDC_ADMINPLAYERLIST;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(12 * GRID_H);
                    w = QUOTE(106 * GRID_W);
                    h = QUOTE(82 * GRID_H);
                    onLBSelChanged = "[""playerLbSelectionChanged""] spawn A3A_fnc_playerManagementTab";

                    sizeEx = QUOTE(GUI_TEXT_SIZE_MEDIUM);
                    rowHeight = QUOTE(4 * GRID_H);
                    columns[] = {0,0.59,0.725};
                };

                class AddMemberButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_ADDMEMBERBUTTON;
                    text = "$STR_antistasi_dialogs_main_admin_add_member_button";
                    onButtonClick = "[""adminAddMember""] call A3A_fnc_playerManagementTab";
                    show = 0;
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(7 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class RemoveMemberButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_REMOVEMEMBERBUTTON;
                    text = "$STR_antistasi_dialogs_main_admin_remove_member_button";
                    onButtonClick = "[""adminRemoveMember""] call A3A_fnc_playerManagementTab";
                    show = 0;
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(7 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class TeleportToPlayerButton : A3A_ShortcutButton
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_to_player_button";
                    onButtonClick = "hint ""Placeholder\nWill use new function when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(22 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class TeleportPlayerButton : A3A_ShortcutButton
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_tp_player_to_me_button";
                    onButtonClick = "hint ""Placeholder\nWill use new function when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(37 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class KickPlayerButton : A3A_ShortcutButton
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_kick_player_button";
                    onButtonClick = "hint ""Placeholder\nWill use new function when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(52 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class BanPlayerButton : A3A_ShortcutButton
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_ban_player_button";
                    onButtonClick = "hint ""Placeholder\nWill use new function when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(67 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class CopyIdButton : A3A_ShortcutButton
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_main_admin_copy_uid_button";
                    onButtonClick = "hint ""Placeholder\nWill use new function when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(120 * GRID_W);
                    y = QUOTE(82 * GRID_H);
                    w = QUOTE(32 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };
            };
        };


        // Close and Back buttons
        class BackButton : A3A_BackButton
        {
            idc = A3A_IDC_MAINDIALOGBACKBUTTON;
            x = QUOTE(DIALOG_X + DIALOG_W * GRID_W - 12 * GRID_W);
            y = QUOTE(DIALOG_Y - 10 * GRID_H);
        };

        class CloseButton : A3A_CloseButton
        {
            idc = -1;
            x = QUOTE(DIALOG_X + DIALOG_W * GRID_W - 5 * GRID_W);
            y = QUOTE(DIALOG_Y - 10 * GRID_H);
        };
    };
};
