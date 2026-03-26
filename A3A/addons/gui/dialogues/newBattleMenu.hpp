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
            h = 5 * GRID_H;
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
            h = 5 * GRID_H;
        };

        // -- MAP (y=10..66, x=0..90) -----------------------------------------
        // Direct child -- never nest A3A_MapControl inside a controlsGroup.
        class Map : A3A_MapControl
        {
            idc = A3A_IDC_NEWBATTLEMENU_MAP;
            x = DIALOG_X;
            y = DIALOG_Y + 11 * GRID_H;
            w = 88 * GRID_W;
            h = 55 * GRID_H;
        };

        // -- TOP-LEFT: PRIMARY NAV TABS (y=0..10, x=0..90) --------------------
        // Operations / Supports / Personnel / Context.
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
                    w = 90 * GRID_W;
                    h = 10 * GRID_H;
                };
                // Four buttons: w=18 h=8; m=3, g=4
                // x positions: 3, 25, 47, 69  (all end at x=87, +3 margin = 90)
                class OperationsTabButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_OPERATIONS;
                    text = $STR_antistasi_dialogs_new_battle_menu_operations_button;
                    onButtonClick = "['OPERATIONS'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 3 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class SupportsTabButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_SUPPORTS;
                    text = $STR_antistasi_dialogs_new_battle_menu_supports_button;
                    onButtonClick = "['SUPPORTS'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 25 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class PersonnelTabButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_PERSONNEL;
                    text = $STR_antistasi_dialogs_new_battle_menu_personnel_button;
                    onButtonClick = "['PERSONNEL'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 47 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextTabButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_TAB_CONTEXT;
                    text = $STR_antistasi_dialogs_new_battle_menu_context_tab_button;
                    onButtonClick = "['CONTEXT'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 69 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
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
                    onButtonClick = "['GAME_OPTIONS'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 1 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class DialogSettingsButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_SETTINGS;
                    text = $STR_antistasi_dialogs_new_battle_menu_settings_button;
                    onButtonClick = "['DIALOG_SETTINGS'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 21 * GRID_W;
                    y = 1 * GRID_H;
                    w = 8 * GRID_W;
                    h = 8 * GRID_H;
                };
            };
        };

        // -- RIGHT PANEL: SECONDARY NAV TABS (y=10..66, x=90..120) -----------
        // Four stacked buttons. Script changes their text when the primary tab
        // switches and highlights the active one. Hidden by script in Context mode.
        // Default labels reflect the Operations primary tab:
        //   Btn1=HQ Management, Btn2=Garrison Management,
        //   Btn3=Emplacement Management, Btn4=Mission Management
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
                class SecondaryTab1 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN1;
                    text = $STR_antistasi_dialogs_new_battle_menu_hq_mgmt_button;
                    onButtonClick = "['SECONDARY_1'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 1 * GRID_W;
                    y = 2 * GRID_H;
                    w = 28 * GRID_W;
                    h = 8 * GRID_H;
                };
                class SecondaryTab2 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN2;
                    text = $STR_antistasi_dialogs_new_battle_menu_garrison_mgmt_button;
                    onButtonClick = "['SECONDARY_2'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 1 * GRID_W;
                    y = 14 * GRID_H;
                    w = 28 * GRID_W;
                    h = 8 * GRID_H;
                };
                class SecondaryTab3 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN3;
                    text = $STR_antistasi_dialogs_new_battle_menu_emplacement_mgmt_button;
                    onButtonClick = "['SECONDARY_3'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 1 * GRID_W;
                    y = 26 * GRID_H;
                    w = 28 * GRID_W;
                    h = 8 * GRID_H;
                };
                class SecondaryTab4 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_MAINTAB_BTN4;
                    text = $STR_antistasi_dialogs_new_battle_menu_mission_mgmt_button;
                    onButtonClick = "['SECONDARY_4'] call A3A_fnc_newBattleMenu_handleTabSwitch;";
                    x = 1 * GRID_W;
                    y = 37 * GRID_H;
                    w = 28 * GRID_W;
                    h = 8 * GRID_H;
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
            y = DIALOG_Y + 10 * GRID_H;
            w = 30 * GRID_W;
            h = 56 * GRID_H;

            class Controls
            {
                class PanelBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.8};
                    x = 0;
                    y = 0;
                    w = 30 * GRID_W;
                    h = 56 * GRID_H;
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

        // -- BOTTOM: CONTEXT BAR (y=66..85, full width, always visible) ------
        // 12 action button slots in a 6x2 grid spanning the full dialog width.
        //   w=18 per button, gap=2, margin=1; columns at x=1,21,41,61,81,101.
        //   Row 1: y=1,h=8  |  Row 2: y=10,h=8
        //   Script sets text and show/hide per slot. Unused slots are hidden.
        class ContextMenuContainer : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_CONTEXT;
            x = DIALOG_X;
            y = DIALOG_Y + 66 * GRID_H;
            w = DIALOG_W * GRID_W;
            h = 19 * GRID_H;

            class Controls
            {
                class TabBackground : A3A_Background
                {
                    idc = -1;
                    colorBackground[] = {0,0,0,0.8};
                    x = 0;
                    y = 0;
                    w = 120 * GRID_W;
                    h = 19 * GRID_H;
                };
                // -- Row 1 (y=1): action buttons 1-6 (w=18, gap=2, margin=1) --
                class ContextButton1 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON1;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_1'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 1 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton2 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON2;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_2'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 21 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton3 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON3;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_3'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 41 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton4 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON4;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_4'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 61 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton5 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON5;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_5'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 81 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton6 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON6;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_6'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 101 * GRID_W;
                    y = 1 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                // -- Row 2 (y=10): action buttons 7-12 --
                class ContextButton7 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON7;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_7'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 1 * GRID_W;
                    y = 10 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton8 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON8;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_8'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 21 * GRID_W;
                    y = 10 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton9 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON9;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_9'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 41 * GRID_W;
                    y = 10 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton10 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON10;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_10'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 61 * GRID_W;
                    y = 10 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton11 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON11;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_11'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 81 * GRID_W;
                    y = 10 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
                class ContextButton12 : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_CONTEXT_BUTTON12;
                    text = "";
                    onButtonClick = "['CONTEXT_ACTION_12'] call A3A_fnc_newBattleMenu_handleContextAction;";
                    x = 101 * GRID_W;
                    y = 10 * GRID_H;
                    w = 18 * GRID_W;
                    h = 8 * GRID_H;
                };
            };
        };

        // -- NAVIGATION BAR (y=85..90, full width) --------------------------
        // Three equal-width navigation buttons: Back, Home, Menu.
        class NavigationBar : A3A_controlsGroupNoScrollbars
        {
            idc = A3A_IDC_NEWBATTLEMENU_NAVBAR;
            x = DIALOG_X;
            y = DIALOG_Y + 85 * GRID_H;
            w = DIALOG_W * GRID_W;
            h = 5 * GRID_H;

            class Controls
            {
                class NavBackground : A3A_Background
                {
                    idc = -1;
                    x = 0;
                    y = 0;
                    w = 120 * GRID_W;
                    h = 5 * GRID_H;
                };
                class BackButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_BACKBUTTON;
                    text = $STR_antistasi_dialogs_new_battle_menu_back_button;
                    onButtonClick = "['NAV_BACK'] call A3A_fnc_newBattleMenu_handleNavigation;";
                    x = 1 * GRID_W;
                    y = 1 * GRID_H;
                    w = 38 * GRID_W;
                    h = 3 * GRID_H;
                };
                class HomeButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_HOMEBUTTON;
                    text = $STR_antistasi_dialogs_new_battle_menu_home_button;
                    onButtonClick = "['NAV_HOME'] call A3A_fnc_newBattleMenu_handleNavigation;";
                    x = 41 * GRID_W;
                    y = 1 * GRID_H;
                    w = 38 * GRID_W;
                    h = 3 * GRID_H;
                };
                class MenuButton : A3A_Button
                {
                    idc = A3A_IDC_NEWBATTLEMENU_MENUBUTTON;
                    text = $STR_antistasi_dialogs_new_battle_menu_menu_button;
                    onButtonClick = "['NAV_MENU'] call A3A_fnc_newBattleMenu_handleNavigation;";
                    x = 81 * GRID_W;
                    y = 1 * GRID_H;
                    w = 38 * GRID_W;
                    h = 3 * GRID_H;
                };
            };
        };
    };
};
