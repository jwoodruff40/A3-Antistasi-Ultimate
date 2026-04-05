// Layout (pixelGrid units, origin = DIALOG_X / DIALOG_Y):
// DIALOG_W=120; left area (map+tabs)=90, right panel=30, total=120.
//
//   x=0                          x=90   x=120
//   y=-5  [======== Rebel Menu ================]
//   y=0   [Operations|Supports|Personnel|Ctx  ][Game Opts|⚙]
//   y=10  [                                   ][             ]
//         [              MAP                  ][ Secondary   ]  <- or RightPanelContext
//         [                                   ][   tabs      ]
//         [                                   ][   (4 stacked]
//         [                                   ][    buttons, ]
//         [                                   ][    script   ]
//         [                                   ][    manages) ]
//   y=66  [                                   ][             ]
//         [Btn1 | Btn2 | Btn3 | Btn4 | Btn5 | Btn6    (w=120)]
//         [Btn7 | Btn8 | Btn9 | Btn10| Btn11| Btn12   (w=120)]
//   y=85  [<                    o                    |        ]
//   y=90
//
// Primary tabs top-left select the active section. Right panel secondary tabs
// change labels per primary tab (Operations/Supports/Personnel/Game Options).
// When Context primary tab is active, RightPanelContextContainer (preview image
// + info text) is shown instead of the secondary tab buttons.
// Context bar is always visible; script sets action button text per section.
//
// IMPORTANT: A3A_MapControl must be a direct child of Controls -- placing it
// inside a controlsGroup offsets the interactable area from what is drawn.
// Also ensure no controlsGroup rectangle overlaps the map rectangle.

class A3A_newBattleMenu
{
    idd = A3A_IDD_NEWBATTLEMENU;
    onLoad = "['onLoad'] spawn A3A_fnc_newBattleMenu";
    onUnload = "['onUnload'] call A3A_fnc_newBattleMenu";

    #define DIALOG_W 120 // Width of dialog in pixelGrid units
    #define DIALOG_H 90 // Height of dialog in pixelGrid units
    #define DIALOG_X CENTER_X(DIALOG_W) // Global x pos of dialog
    #define DIALOG_Y CENTER_Y(DIALOG_H) // Global y pos of dialog

    class ControlsBackground
    {
        class TitleBarBackground : A3A_Background
        {
            moving = true;
            colorBackground[] = A3A_COLOR_TITLEBAR_BACKGROUND;
            x = DIALOG_X;
            y = DIALOG_Y - 5 * GRID_H;
            w = DIALOG_W * GRID_W;
            h = 4 * GRID_H;
        };

        class Background : A3A_Background
        {
            x = DIALOG_X;
            y = DIALOG_Y;
            w = DIALOG_W * GRID_W;
            h = DIALOG_H * GRID_H;
        };
    };

    class Controls
    {
        // -- HEADER ----------------------------------------------------------
        class HeaderBar : A3A_TitlebarText
        {
            idc = -1;
            text = $STR_antistasi_dialogs_new_battle_menu_header;
            style = ST_CENTER;
            x = DIALOG_X;
            y = DIALOG_Y - 5 * GRID_H;
            w = DIALOG_W * GRID_W;
            h = 4 * GRID_H;
        };

        // -- MAP (y=10..66, x=0..90) -----------------------------------------
        // Direct child -- never nest A3A_MapControl inside a controlsGroup.
        class Map : A3A_MapControl
        {
            idc = A3A_IDC_NEWBATTLEMENU_MAP;
            x = DIALOG_X + 1 * GRID_W;
            y = DIALOG_Y + 11 * GRID_H;
            w = 88 * GRID_W;
            h = 55 * GRID_H;
        };

        // -- TOP-LEFT: PRIMARY NAV TABS (y=0..10, x=0..90) --------------------
        // Clicking a primary tab calls A3A_fnc_newBattleMenu_handleTabSwitch with:
        //   ['PRIMARY', sectionName]
        // The handler:
        //   1. Highlights the active primary tab.
        //   2. Shows/hides MainTabsContainer vs RightPanelContextContainer.
        //   3. Relabels the four secondary tab buttons per the section mapping below.
        //   4. Selects the first secondary tab by default.
        //
        // Section → secondary tabs:
        //   OPERATIONS:   [1]HQ Management, [2]Garrison Mgmt, [3]Outpost Mgmt, [4]Mission Mgmt
        //   SUPPORTS:     [1]Offensive,     [2]Defensive,     [3]Reconnaissance,   [4]Supply
        //   PERSONNEL:    [1]Player,        [2]Commander,     [3]AI Recruitment,   [4]AI Management
        //   GAME_OPTIONS: [1]Environment,   [2]Performance,   [3]Server Info,      [4]Save
        //   CONTEXT:      MainTabsContainer hidden; RightPanelContextContainer shown.
        //   SETTINGS:     Single secondary button visible: 'Default Tab' selector.
        //
        // Active tab is highlighted by the script.
        class PrimaryTabsContainer : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_PRIMARYTABS;
            x = DIALOG_X;
            y = DIALOG_Y;
            w = 90 * GRID_W;
            h = 10 * GRID_H;

            class Controls
            {
                class TabBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.8};
                    x = 0;
                    y = 0;
                    w = 89 * GRID_W;
                    h = 10 * GRID_H;
                };
                // Four buttons: w=18 h=8; m=3, g=4
                // x positions: 3, 25, 47, 69  (all end at x=87, +3 margin = 90)
                class OperationsTabButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_OPERATIONS;
                    text = $STR_antistasi_dialogs_new_battle_menu_operations_button;
                    onButtonClick = "[""handleTabSwitch"", [""PRIMARY"", ""OPERATIONS""]] call A3A_fnc_newBattleMenu;";
                    x = 3 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class SupportsTabButton : OperationsTabButton
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_SUPPORTS;
                    text = $STR_antistasi_dialogs_new_battle_menu_supports_button;
                    onButtonClick = "[""handleTabSwitch"", [""PRIMARY"", ""SUPPORTS""]] call A3A_fnc_newBattleMenu;";
                    x = 25 * GRID_W;
                };
                class PersonnelTabButton : OperationsTabButton
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_PERSONNEL;
                    text = $STR_antistasi_dialogs_new_battle_menu_personnel_button;
                    onButtonClick = "[""handleTabSwitch"", [""PRIMARY"", ""PERSONNEL""]] call A3A_fnc_newBattleMenu;";
                    x = 47 * GRID_W;
                };
                class ContextTabButton : OperationsTabButton
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_CONTEXT;
                    text = $STR_antistasi_dialogs_new_battle_menu_context_tab_button;
                    // Hides MainTabsContainer, shows RightPanelContextContainer.
                    onButtonClick = "[""handleTabSwitch"", [""PRIMARY"", ""CONTEXT""]] call A3A_fnc_newBattleMenu;";
                    x = 69 * GRID_W;
                };
            };
        };

        // -- TOP-RIGHT: GAME OPTIONS + SETTINGS (y=0..10, x=90..120) ---------
        class GameOptionsContainer : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_OPTIONS;
            x = DIALOG_X + 90 * GRID_W;
            y = DIALOG_Y;
            w = 30 * GRID_W;
            h = 10 * GRID_H;

            class Controls
            {
                class TabBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.8};
                    x = 0;
                    y = 0;
                    w = 30 * GRID_W;
                    h = 10 * GRID_H;
                };
                class GameOptionsTabButton : A3A_Button
                {
                    idc = -1;
                    text = $STR_antistasi_dialogs_new_battle_menu_game_options_button;
                    onButtonClick = "[""handleTabSwitch"", [""PRIMARY"", ""GAME_OPTIONS""]] call A3A_fnc_newBattleMenu;";
                    x = 1 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class DialogSettingsButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_SETTINGS;
                    text = $STR_antistasi_dialogs_new_battle_menu_settings_button;
                    // Opens dialog settings (default tab picker); shows single secondary tab.
                    onButtonClick = "[""handleTabSwitch"", [""PRIMARY"", ""SETTINGS""]] call A3A_fnc_newBattleMenu;";
                    x = 21 * GRID_W;
                    y = 1 * GRID_H;
                    w = 8 * GRID_W;
                    h = 8 * GRID_H;
                };
            };
        };

        // -- RIGHT PANEL: SECONDARY NAV TABS (y=10..66, x=90..120) -----------
        // Four stacked buttons; script relabels them and highlights the active one
        // whenever the primary tab changes.  Hidden (show=0) when Context or
        // Settings is the active primary — RightPanelContextContainer overlays instead.
        //
        // Clicking a secondary tab calls A3A_fnc_newBattleMenu_handleTabSwitch with:
        //   ['SECONDARY', buttonIndex]   (buttonIndex = 1..4)
        // The handler uses the current primary section to determine which sub-section
        // was selected, then repopulates the context bar action buttons accordingly.
        //
        // Context bar actions per primary → secondary combination (from UI spec):
        //   OPERATIONS / HQ Management:
        //     Move HQ | Train Rebel Troops | Set Rebel Loadouts | Clear Forest
        //   OPERATIONS / Garrison Management:
        //     Disband Units/Post | Recruit Units
        //     (right panel info shows selected garrison: name, unit breakdown)
        //   OPERATIONS / Outpost Management:
        //     Establish Watchpost | Establish Roadblock | Establish HMG Emplacement |
        //     Establish AT Emplacement | Establish AA Emplacement |
        //     Establish AP Minefield | Establish AT Minefield
        //     (right panel info: 'Establish' title + 'Cost: %1 HR, %2 $')
        //   OPERATIONS / Mission Management:
        //     Request Assassination | Request Convoy | Request Destroy |
        //     Request Logistics | Request Rescue | Request Conquest | Request Supply
        //     (right panel info: 'Active Missions' title + active mission list)
        //   SUPPORTS / Offensive:
        //     HE Bomb Airstrike | Cluster Bomb Airstrike | Chemical Bomb Airstrike |
        //     Napalm Airstrike | Paradrop Plane Run
        //   SUPPORTS / Defensive:
        //     Smoke Barrage | Flare Barrage
        //   SUPPORTS / Reconnaissance:
        //     Recon Plane Run
        //   SUPPORTS / Supply:
        //     Light Vehicle Airdrop | Supply Crate Airdrop | Loot Helicopter Run
        //   PERSONNEL / Player:
        //     Toggle Music | Toggle Paradrop | Toggle Teardown | Donate Money to Player
        //   PERSONNEL / Commander:
        //     Check Victory | Reset Arms Dealer | Train Rebel Troops | Set Rebel Loadouts |
        //     Set Arsenal Limits | Place Rally Point | Remove Rally Point |
        //     Share Faction Money | Resign / Toggle Eligibility |
        //     Add Server Member | Remove Server Member
        //   PERSONNEL / AI Recruitment:
        //     Infantry Squad | Infantry Team | AT Team | AT Car | Snipers | AA Truck |
        //     MG Team | Mortar Team | Vehicle Crew | MG Car
        //   PERSONNEL / AI Management:
        //     AI Control | HC Transfer | Garrison Unit/Squad | Dismiss Unit/Squad |
        //     Auto Rearm/Loot | SITREP | Assign Vehicle | (Dis)mount Vehicle
        //   GAME_OPTIONS / Environment:
        //     Fog Level | Overcast Level
        //   GAME_OPTIONS / Performance:
        //     Garbage Clean
        //   GAME_OPTIONS / Server Info:
        //     WorldName | Version | Time since last GC
        //   GAME_OPTIONS / Save:
        //     Persistent Save | Edit Save Parameters
        //   SETTINGS / Default Tab:
        //     Operations | Supports | Personnel | Context  (sets the default open tab)
        //   CONTEXT (primary tab active — handled by RightPanelContextContainer):
        //     Vehicle selected:  Garage Vehicle | Unlock Vehicle | Moveout Vehicle Crew |
        //                        Flip Vehicle | Sell Vehicle | Add to Air Support |
        //                        Move Static (static weapons only)
        //     Unit/group selected: AI Control | HC Transfer | Garrison Unit/Squad |
        //                        Dismiss Unit/Squad | Auto Rearm/Loot | SITREP |
        //                        Assign Vehicle | (Dis)mount Vehicle |
        //                        Donate Money to Player | Add Server Member | Remove Server Member
        class SecondaryTabsContainer : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_MAINTABS;
            x = DIALOG_X + 90 * GRID_W;
            y = DIALOG_Y + 11 * GRID_H;
            w = 30 * GRID_W;
            h = 55 * GRID_H;

            class Controls
            {
                class TabBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.8};
                    x = 0;
                    y = 0;
                    w = 30 * GRID_W;
                    h = 55 * GRID_H;
                };
                class SecondaryTab1 : A3A_ControlsGroupNoScrollbars
                {
                    x = 1 * GRID_W;
                    y = 2 * GRID_H;
                    w = 28 * GRID_W;
                    h = 8 * GRID_H;

                    class Controls
                    {
                        class Button : A3A_Button_Transparent
                        {
                            idc = -1;
                            onButtonClick = "[""handleTabSwitch"", [""SECONDARY"", 1]] call A3A_fnc_newBattleMenu;";
                            w = 28 * GRID_W;
                            h = 8 * GRID_H;
                        };
                        class Label : A3A_Text
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN1;
                            text = $STR_antistasi_dialogs_new_battle_menu_hq_mgmt_button;
                            colorBackground[] = A3A_COLOR_BUTTON_BACKGROUND;
                            colorBackgroundDisabled[] = A3A_COLOR_BUTTON_BACKGROUND_DISABLED;
                            colorBackgroundActive[] =	A3A_COLOR_BUTTON_ACTIVE;
                            size = GUI_TEXT_SIZE_SMALL;
                            sizeEx = GUI_TEXT_SIZE_SMALL;
                            style = ST_CENTER + ST_MULTI + ST_NO_RECT; // ST_UPPERCASE doesn't work with ST_MULTI :(
                            w = 28 * GRID_W;
                            h = 8 * GRID_H;
                        };
                    };
                };
                class SecondaryTab2 : SecondaryTab1
                {
                    y = 13 * GRID_H;
                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleTabSwitch"", [""SECONDARY"", 2]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN2;
                            text = $STR_antistasi_dialogs_new_battle_menu_garrison_mgmt_button;
                        };
                    };
                };
                class SecondaryTab3 : SecondaryTab1
                {
                    y = 26 * GRID_H;
                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleTabSwitch"", [""SECONDARY"", 3]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN3;
                            text = $STR_antistasi_dialogs_new_battle_menu_outpost_mgmt_button;
                        };
                    };
                };
                class SecondaryTab4 : SecondaryTab1
                {
                    y = 39 * GRID_H;
                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleTabSwitch"", [""SECONDARY"", 4]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN4;
                            text = $STR_antistasi_dialogs_new_battle_menu_mission_mgmt_button;
                        };
                    };
                };
            };
        };

        // -- RIGHT PANEL: CONTEXT VIEW (y=10..66, x=90..120) -----------------
        // Shown by script (show=1) when the Context primary tab is active.
        // Overlays SecondaryTabsContainer. Preview image fills the upper portion;
        // multi-line info text occupies the lower portion.
        class RightPanelContextContainer : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_RIGHTPANEL_CONTEXT;
            show = 0;
            x = DIALOG_X + 90 * GRID_W;
            y = DIALOG_Y + 11 * GRID_H;
            w = 30 * GRID_W;
            h = 55 * GRID_H;

            class Controls
            {
                class PanelBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.8};
                    x = 0;
                    y = 0;
                    w = 30 * GRID_W;
                    h = 55 * GRID_H;
                };
                // Preview image -- script sets texture to entity/vehicle model picture.
                class PreviewImage : A3A_Picture
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_PREVIEW;
                    x = 1 * GRID_W;
                    y = 1 * GRID_H;
                    w = 28 * GRID_W;
                    h = 25 * GRID_H;
                };
                // Multi-line info text below preview (e.g., unit counts, stats).
                class RightPanelInfo : A3A_Text
                {
                    idc = A3A_IDC_NEWBATTLEMENU_RIGHTPANEL_INFO;
                    style = ST_MULTI;
                    x = 1 * GRID_W;
                    y = 27 * GRID_H;
                    w = 28 * GRID_W;
                    h = 28 * GRID_H;
                };
            };
        };

        // -- BOTTOM: CONTEXT BAR (y=67..85, full width, always visible) ------
        // 12 action button slots in a 6x2 grid spanning the full dialog width.
        //   w=18 per button, gap=2, margin=1; columns at x=1,21,41,61,81,101.
        //   Row 1: y=1,h=8  |  Row 2: y=10,h=8
        //   Script sets text and show/hide per slot. Unused slots are hidden.
        class ContextMenuContainer : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT;
            x = DIALOG_X;
            y = DIALOG_Y + 67 * GRID_H;
            w = DIALOG_W * GRID_W;
            h = 18 * GRID_H;

            class Controls
            {
                class TabBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.8};
                    x = 0;
                    y = 0;
                    w = 120 * GRID_W;
                    h = 18 * GRID_H;
                };
                // -- Row 1 (y=1): action buttons 1-6 (w=18, gap=2, margin=1) --
                class ContextButton1 : A3A_ControlsGroupNoScrollbars
                {
                    x = 1 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;

                    class Controls
                    {
                        class Button : A3A_Button_Transparent
                        {
                            idc = -1;
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_1""]] call A3A_fnc_newBattleMenu;";
                            w = 18 * GRID_W;
                            h = 8 * GRID_H;
                        };
                        class Label : A3A_Text
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON1;
                            text = "";
                            colorBackground[] = A3A_COLOR_BUTTON_BACKGROUND;
                            colorBackgroundDisabled[] = A3A_COLOR_BUTTON_BACKGROUND_DISABLED;
                            colorBackgroundActive[] =	A3A_COLOR_BUTTON_ACTIVE;
                            size = GUI_TEXT_SIZE_SMALL;
                            sizeEx = GUI_TEXT_SIZE_SMALL;
                            style = ST_CENTER + ST_MULTI + ST_NO_RECT; // ST_UPPERCASE doesn't work with ST_MULTI :(
                            w = 18 * GRID_W;
                            h = 8 * GRID_H;
                        };
                    };
                };
                class ContextButton2 : ContextButton1
                {
                    x = 21 * GRID_W;

                    class Controls : Controls
                    {
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON2;
                        };
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_2""]] call A3A_fnc_newBattleMenu;";
                        };
                    };
                };
                class ContextButton3 : ContextButton1
                {
                    x = 41 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_3""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON3;
                        };
                    };
                };
                class ContextButton4 : ContextButton1
                {
                    x = 61 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_4""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON4;
                        };
                    };
                };
                class ContextButton5 : ContextButton1
                {
                    x = 81 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_5""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON5;
                        };
                    };
                };
                class ContextButton6 : ContextButton1
                {
                    x = 101 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_6""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON6;
                        };
                    };
                };
                class ContextButton7 : ContextButton1
                {
                    y = 10 * GRID_H;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_7""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON7;
                        };
                    };
                };
                class ContextButton8 : ContextButton7
                {
                    x = 21 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_8""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON8;
                        };
                    };
                };
                class ContextButton9 : ContextButton7
                {
                    x = 41 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_9""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON9;
                        };
                    };
                };
                class ContextButton10 : ContextButton7
                {
                    x = 61 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_10""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON10;
                        };
                    };
                };
                class ContextButton11 : ContextButton7
                {
                    x = 81 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_11""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON11;
                        };
                    };
                };
                class ContextButton12 : ContextButton7
                {
                    x = 101 * GRID_W;

                    class Controls : Controls
                    {
                        class Button : Button
                        {
                            onButtonClick = "[""handleContextAction"", [""CONTEXT_ACTION_12""]] call A3A_fnc_newBattleMenu;";
                        };
                        class Label : Label
                        {
                            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON12;
                        };
                    };
                };
            };
        };

        // -- NAVIGATION BAR (y=85..90, full width) --------------------------
        // Three equal-width navigation buttons: Back, Home, Menu.
        class NavigationBar : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_NAVBAR;
            x = DIALOG_X;
            y = DIALOG_Y + 86 * GRID_H;
            w = DIALOG_W * GRID_W;
            h = 4 * GRID_H;

            class Controls
            {
                class NavBackground : A3A_Background
                {
                    idc = -1;
                    x = 0;
                    y = 0;
                    w = 120 * GRID_W;
                    h = 4 * GRID_H;
                };
                class BackButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_BACKBUTTON;
                    text = $STR_antistasi_dialogs_new_battle_menu_back_button;
                    onButtonClick = "[""handleNavigation"", [""NAV_BACK""]] call A3A_fnc_newBattleMenu;";
                    x = 4 * GRID_W;
                    y = 0;
                    w = 4 * GRID_W;
                    h = 4 * GRID_H;
                };
                class HomeButton : BackButton
                {
                    idc = A3A_IDC_NEWBATTLEMENU_HOMEBUTTON;
                    text = $STR_antistasi_dialogs_new_battle_menu_home_button;
                    onButtonClick = "[""handleNavigation"", [""NAV_HOME""]] call A3A_fnc_newBattleMenu;";
                    x = 58 * GRID_W;
                };
                class MenuButton : BackButton
                {
                    idc = A3A_IDC_NEWBATTLEMENU_MENUBUTTON;
                    text = $STR_antistasi_dialogs_new_battle_menu_menu_button;
                    onButtonClick = "[""handleNavigation"", [""NAV_MENU""]] call A3A_fnc_newBattleMenu;";
                    x = 112 * GRID_W;
                };
            };
        };
    };
};

// ! Reset dialog dimensions to avoid breaking other UI dialogs
#define DIALOG_W 160 // Width of dialog in pixelGrid units
#define DIALOG_H 100 // Height of dialog in pixelGrid units
