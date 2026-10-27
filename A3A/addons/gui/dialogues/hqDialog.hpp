class A3A_HqDialog : A3A_DefaultDialog
{
    idd = A3A_IDD_HQDIALOG;
    onLoad = "[""onLoad""] spawn A3A_fnc_hqDialog";

    class Controls
    {
        class TitlebarText : A3A_TitlebarText
        {
            idc = A3A_IDC_HQDIALOGTITLEBAR;
            text = "$STR_antistasi_dialogs_hq_titlebar";
            x = QUOTE(DIALOG_X);
            y = QUOTE(DIALOG_Y - 5 * GRID_H);
            w = QUOTE(DIALOG_W * GRID_W);
            h = QUOTE(5 * GRID_H);
        };

        // Main content
        class MainTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_HQDIALOGMAINTAB;

            class controls
            {
                // Left side buttons

                class GarrisonsIcon : A3A_Picture
                {
                    idc = -1;
                    text = A3A_Icon_Garrison;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(13 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class GarrisonManagementButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_garrisons_button";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    onButtonClick = "[""switchTab"",[""garrison""]] call A3A_fnc_hqDialog";
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(11 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class MinefieldsIcon : A3A_Picture
                {
                    idc = -1;
                    text = A3A_Icon_Minefield;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(34 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class MinefieldsButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_minefields_button";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    onButtonClick = "[""switchTab"",[""minefields""]] call A3A_fnc_hqDialog";
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(32 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class MoveHqIcon : A3A_Picture
                {
                    idc = A3A_IDC_MOVEHQICON;
                    text = A3A_Icon_Move_HQ;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(55 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class MoveHqButton : A3A_Button
                {
                    idc = A3A_IDC_MOVEHQBUTTON;
                    text = "$STR_antistasi_dialogs_hq_move_hq_button";
                    onButtonClick = "[] spawn A3A_fnc_moveHQ; closeDialog 0";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(53 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class ClearTreesIcon : A3A_Picture
                {
                    idc = -1;
                    text = A3A_Icon_Clear_Trees;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(76 * GRID_H);
                    w = QUOTE(8 * GRID_W);
                    h = QUOTE(8 * GRID_H);
                };

                class ClearTreesButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_clear_trees_button";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    onButtonClick = "[] spawn A3A_fnc_clearForest";
                    x = QUOTE(20 * GRID_W);
                    y = QUOTE(74 * GRID_H);
                    w = QUOTE(36 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                // Campaign status section
                class CampaignStatusControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = -1;
                    x = QUOTE(70 * GRID_W);
                    y = QUOTE(7 * GRID_H);
                    w = QUOTE(90 * GRID_W);
                    h = QUOTE(23 * GRID_H);

                    class controls
                    {
                        class CampaignStatusLabel : A3A_SectionLabelRight
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_campaign_status";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(90 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class WarLevelLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_war_level";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(14 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class WarLevelText : A3A_Text
                        {
                            idc = A3A_IDC_WARLEVELTEXT;
                            style = ST_RIGHT;
                            text = "1";
                            x = QUOTE(14 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(14 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class AggressionLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_aggression";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(11 * GRID_H);
                            w = QUOTE(28 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class OccFlagPicture : A3A_Picture
                        {
                            idc = A3A_IDC_OCCFLAGPICTURE;
                            x = QUOTE(1 * GRID_W);
                            y = QUOTE(16 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };

                        class OccAggroText : A3A_Text
                        {
                            idc = A3A_IDC_OCCAGGROTEXT;
                            style = ST_CENTER;
                            colorBackground[] = A3A_COLOR_BACKGROUND;
                            shadow = 2;
                            x = QUOTE(1 * GRID_W);
                            y = QUOTE(16 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };

                        class InvFlagPicture : A3A_Picture
                        {
                            idc = A3A_IDC_INVFLAGPICTURE;
                            x = QUOTE(16 * GRID_W);
                            y = QUOTE(16 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };

                        class InvAggroText : A3A_Text
                        {
                            idc = A3A_IDC_INVAGGROTEXT;
                            style = ST_CENTER;
                            colorBackground[] = A3A_COLOR_BACKGROUND;
                            shadow = 2;
                            x = QUOTE(16 * GRID_W);
                            y = QUOTE(16 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };


                        // Controlled locations

                        class ControlledCitiesIcon : A3A_Picture
                        {
                            idc = A3A_IDC_CONTROLLEDCITIESICON;
                            text = A3A_Icon_Town;
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_cities";
                            x = QUOTE(32 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledCitiesText : A3A_Text
                        {
                            idc = A3A_IDC_CONTROLLEDCITIESTEXT;
                            text = "";
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_cities";
                            x = QUOTE(36 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledOutpostsIcon : A3A_Picture
                        {
                            idc = A3A_IDC_CONTROLLEDOUTPOSTSICON;
                            text = A3A_Icon_Outpost;
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_outposts";
                            x = QUOTE(49 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledOutpostsText : A3A_Text
                        {
                            idc = A3A_IDC_CONTROLLEDOUTPOSTSTEXT;
                            text = "";
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_outposts";
                            x = QUOTE(53 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledAirBasesIcon : A3A_Picture
                        {
                            idc = A3A_IDC_CONTROLLEDAIRBASESICON;
                            text = A3A_Icon_Airbase;
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_airbases";
                            x = QUOTE(66 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledAirBasesText : A3A_Text
                        {
                            idc = A3A_IDC_CONTROLLEDAIRBASESTEXT;
                            text = "";
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_airbases";
                            x = QUOTE(70 * GRID_W);
                            y = QUOTE(6 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        ////////////////////////////

                        class ControlledResourcesIcon : A3A_Picture
                        {
                            idc = A3A_IDC_CONTROLLEDRESOURCESICON;
                            text = A3A_Icon_Resource;
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_resources";
                            x = QUOTE(32 * GRID_W);
                            y = QUOTE(11 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledResourcesText : A3A_Text
                        {
                            idc = A3A_IDC_CONTROLLEDRESOURCESTEXT;
                            text = "";
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_resources";
                            x = QUOTE(36 * GRID_W);
                            y = QUOTE(11 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledFactoriesIcon : A3A_Picture
                        {
                            idc = A3A_IDC_CONTROLLEDFACTORIESICON;
                            text = A3A_Icon_Factory;
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_factories";
                            x = QUOTE(49 * GRID_W);
                            y = QUOTE(11 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledFactoriesText : A3A_Text
                        {
                            idc = A3A_IDC_CONTROLLEDFACTORIESTEXT;
                            text = "";
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_factories";
                            x = QUOTE(53 * GRID_W);
                            y = QUOTE(11 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledSeaPortsIcon : A3A_Picture
                        {
                            idc = A3A_IDC_CONTROLLEDSEAPORTSICON;
                            text = A3A_Icon_Seaport;
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_seaports";
                            x = QUOTE(66 * GRID_W);
                            y = QUOTE(11 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class ControlledPortsText : A3A_Text
                        {
                            idc = A3A_IDC_CONTROLLEDSEAPORTSTEXT;
                            text = "";
                            tooltip = "$STR_antistasi_dialogs_hq_controlled_seaports";
                            x = QUOTE(70 * GRID_W);
                            y = QUOTE(11 * GRID_H);
                            w = QUOTE(12 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        // Stupid hack frame because armas normal frames gets off by 1 pixel errors
                        class PopStatusBarFrame : A3A_Background
                        {
                            idc = -1;
                            colorBackground[]= A3A_COLOR_BLACK;
                            x = QUOTE(31 * GRID_W - 1 * pixelW);
                            y = QUOTE(16 * GRID_H - 1 * pixelH);
                            w = QUOTE(50 * GRID_W + 2 * pixelW);
                            h = QUOTE(6 * GRID_H + 2 * pixelH);
                        };

                        class PopStatusBarControlsGroup : A3A_ControlsGroupNoScrollbars
                        {
                            idc = -1;
                            x = QUOTE(31 * GRID_W);
                            y = QUOTE(16 * GRID_H);
                            w = QUOTE(50 * GRID_W);
                            h = QUOTE(6 * GRID_H);

                            class controls
                            {
                                class PopStatusBarBackground : A3A_Background
                                {
                                    idc = -1;
                                    // Intentionally using hardcoded colors here since this isn't intended to be customizeable
                                    colorBackground[] = {0.3,0.3,0.3,1};
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(50 * GRID_W);
                                    h = QUOTE(6 * GRID_H);
                                };

                                class PopStatusBarReb : A3A_Picture
                                {
                                    idc = A3A_IDC_POPSTATUSBARREB;
                                    text = "#(argb,1,1,1)color(0.9,0.9,0.9,1)";
                                    tooltip = "$STR_antistasi_dialogs_hq_popular_support_tooltip";
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(16 * GRID_W);
                                    h = QUOTE(6 * GRID_H);
                                };

                                class PopStatusBarDead : A3A_Picture
                                {
                                    idc = A3A_IDC_POPSTATUSBARDEAD;
                                    text = "#(argb,1,1,1)color(0.15,0.15,0.15,1)";
                                    tooltip = "$STR_antistasi_dialogs_hq_dead_population_tooltip";
                                    x = QUOTE(48 * GRID_W);
                                    y = QUOTE(0 * GRID_H);
                                    w = QUOTE(2 * GRID_W);
                                    h = QUOTE(6 * GRID_H);
                                };

                                // Line for win condition
                                class WinLine : A3A_Text
                                {
                                    idc = -1;
                                    style = ST_MULTI + ST_TITLE_BAR + ST_HUD_BACKGROUND;
                                    text = "";
                                    colorText[] = {0,0,0,1};
                                    colorBackground[] = A3A_COLOR_TRANSPARENT;
                                    x = QUOTE(25 * GRID_W);
                                    y = 0;
                                    w = 0;
                                    h = QUOTE(6 * GRID_H);
                                };

                                // Line for lose condition
                                class LoseLine : A3A_Text
                                {
                                    idc = -1;
                                    style = ST_MULTI + ST_TITLE_BAR + ST_HUD_BACKGROUND;
                                    text = "";
                                    colorText[] = {0,0,0,1};
                                    colorBackground[] = A3A_COLOR_TRANSPARENT;
                                    x = QUOTE(33.33333 * GRID_W);
                                    y = 0;
                                    w = 0;
                                    h = QUOTE(6 * GRID_H);
                                };

                                class PopStatusRebText : A3A_Text
                                {
                                    idc = A3A_IDC_POPSTATUSREBTEXT;
                                    text = ""; // Updated from script
                                    tooltip = "$STR_antistasi_dialogs_hq_popular_support_tooltip";
                                    colorShadow[] = {0,0,0,0.5};
                                    shadow = 2;
                                    x = QUOTE(0 * GRID_W);
                                    y = QUOTE(1 * GRID_H);
                                    w = QUOTE(10 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                                class PopStatusDeadText : A3A_Text
                                {
                                    idc = A3A_IDC_POPSTATUSDEADTEXT;
                                    style = ST_RIGHT;
                                    text = ""; // Updated from script
                                    tooltip = "$STR_antistasi_dialogs_hq_dead_population_tooltip";
                                    colorShadow[] = {0,0,0,0.5};
                                    shadow = 2;
                                    x = QUOTE(40 * GRID_W);
                                    y = QUOTE(1 * GRID_H);
                                    w = QUOTE(10 * GRID_W);
                                    h = QUOTE(4 * GRID_H);
                                };

                            };
                        };

                    };
                };


                // Faction resources section

                class FactionResourcesControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = -1;
                    x = QUOTE(70 * GRID_W);
                    y = QUOTE(33 * GRID_H);
                    w = QUOTE(90 * GRID_W);
                    h = QUOTE(28 * GRID_H);

                    class controls
                    {
                        class FactionResourcesLabel : A3A_SectionLabelRight
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_faction_resources";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(90 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        /* class FactionHRBackground : A3A_Background
                        {
                            idc = -1;
                            x = 0 * GRID_W;
                            y = 7 * GRID_H;
                            w = 60 * GRID_W;
                            h = 9 * GRID_H;
                        }; */

                        class FactionHRLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_hr_label";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(7 * GRID_H);
                            w = QUOTE(39 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class FactionHRText : A3A_Text
                        {
                            idc = A3A_IDC_FACTIONHRTEXT;
                            style = ST_RIGHT;
                            text = "0";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(7 * GRID_H);
                            w = QUOTE(16 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class FactionTrainingLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_training_level_label";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(12 * GRID_H);
                            w = QUOTE(39 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class FactionTrainingText : A3A_Text
                        {
                            idc = A3A_IDC_FACTIONTRAININGTEXT;
                            style = ST_RIGHT;
                            text = "0 / 20";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(12 * GRID_H);
                            w = QUOTE(16 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class TrainTroopsButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_train_button";
                            onButtonClick = "[] call A3A_fnc_FIAskillAdd; [""updateMainTab""] call A3A_fnc_hqDialog"; // TODO UI-update: Update tooltip with price
                            x = QUOTE(60 * GRID_W);
                            y = QUOTE(7 * GRID_H);
                            w = QUOTE(22 * GRID_W);
                            h = QUOTE(9 * GRID_H);
                        };

                        /* class  FactionMoneyBackground : A3A_Background
                        {
                        idc = -1;
                        x = 0 * GRID_W;
                        y = 19 * GRID_H;
                        w = 60 * GRID_W;
                        h = 9 * GRID_H;
                        }; */

                        class FactionMoneyLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_faction_money_label";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(19 * GRID_H);
                            w = QUOTE(39 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class FactionMoneyText : A3A_Text
                        {
                            idc = A3A_IDC_FACTIONMONEYTEXT;
                            style = ST_RIGHT;
                            text = "0";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(19 * GRID_H);
                            w = QUOTE(16 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class FactionMoneySlider : A3A_Slider
                        {
                            idc = A3A_IDC_FACTIONMONEYSLIDER;
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(24 * GRID_H);
                            w = QUOTE(39 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            onSliderPosChanged = "[""factionMoneySliderChanged""] spawn A3A_fnc_hqDialog";
                        };

                        class FactionMoneyEditBox : A3A_Edit
                        {
                            idc = A3A_IDC_FACTIONMONEYEDITBOX;
                            style = ST_RIGHT;
                            text = "0";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(24 * GRID_H);
                            w = QUOTE(16 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            onChar = "[""factionMoneyEditBoxChanged""] spawn A3A_fnc_hqDialog";
                        };

                        class FactionMoneyButton : A3A_Button
                        {
                            idc = A3A_IDC_FACTIONMONEYBUTTON;
                            text = "$STR_antistasi_dialogs_hq_take_money_button";
                            onButtonClick = "[""factionMoneyButtonClicked""] call A3A_fnc_hqDialog"; // TODO UI-update: Replace placeholder when merging
                            x = QUOTE(60 * GRID_W);
                            y = QUOTE(19 * GRID_H);
                            w = QUOTE(22 * GRID_W);
                            h = QUOTE(9 * GRID_H);
                        };

                    };
                };


                // Rest & environment section

                class RestSectionControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = -1;
                    x = QUOTE(70 * GRID_W);
                    y = QUOTE(65 * GRID_H);
                    w = QUOTE(90 * GRID_W);
                    h = QUOTE(26 * GRID_H);

                    class controls
                    {
                        class RestLabel : A3A_SectionLabelRight
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_rest_environment";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(90 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class RestText : A3A_StructuredText
                        {
                            idc = A3A_IDC_RESTTEXT;
                            text = "";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(7 * GRID_H);
                            w = QUOTE(57 * GRID_W);
                            h = QUOTE(10 * GRID_H);
                            colorBackground[] = A3A_COLOR_BACKGROUND;
                        };

                        class RestSlider : A3A_Slider
                        {
                            idc = A3A_IDC_RESTSLIDER;
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(21 * GRID_H);
                            w = QUOTE(39 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            onSliderPosChanged = "[""restSliderChanged""] spawn A3A_fnc_hqDialog";
                        };

                        class RestButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_rest_button";
                            onButtonClick = "[""skipTime""] spawn A3A_fnc_hqDialog;";
                            x = QUOTE(41 * GRID_W); // 108
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(16 * GRID_W);
                            h = QUOTE(6 * GRID_H);
                        };

                        class ClearFogButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_clear_fog_button";
                            onButtonClick = "[10,[0,0,0]] remoteExec [""setFog"",2];";
                            x = QUOTE(60 * GRID_W);
                            y = QUOTE(7 * GRID_H);
                            w = QUOTE(22 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                        class StopRainButton : A3A_Button
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_stop_rain_button";
                            // onButtonClick = "[] call A3A_fnc_stopRain";
                            onButtonClick = "[10,0] remoteExec [""setRain"",2]";
                            x = QUOTE(60 * GRID_W);
                            y = QUOTE(18 * GRID_H);
                            w = QUOTE(22 * GRID_W);
                            h = QUOTE(8 * GRID_H);
                        };

                    };
                };

            };
        };

        // Map misbehaves inside controlsGroups, hence this is placed outside
        // See controls.hpp for details
        class GarrisonMap : A3A_MapControl
        {
            idc = A3A_IDC_GARRISONMAP;
            onMouseButtonClick = "[""garrisonMapClicked"", [[_this select 2, _this select 3]]] call A3A_fnc_hqDialog";
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

        class GarrisonTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_HQDIALOGGARRISONTAB;
            // Width set to smaller than usual to avoid an issue where
            // pressing anything other than the map would (invisibly) cover up the
            // map control, making it unclickable
            w = QUOTE(68 * GRID_W);

            class controls
            {
                class GarrisonTitle : A3A_Text
                {
                    idc = A3A_IDC_GARRISONTITLE;
                    text = "";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    colorBackground[] = A3A_COLOR_BLACK;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(8 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class GarrisonBackground : A3A_Background
                {
                    idc = -1;
                    x = QUOTE(8 * GRID_W);
                    y = QUOTE(14 * GRID_H);
                    w = QUOTE(54 * GRID_W);
                    h = QUOTE(60 * GRID_H);
                };

                class GarrisonControlsGroup : A3A_ControlsGroupNoScrollbars
                {
                    idc = -1;
                    x = QUOTE(10 * GRID_W);
                    y = QUOTE(17 * GRID_H);
                    w = QUOTE(50 * GRID_W);
                    h = QUOTE(41 * GRID_H);

                    class controls
                    {
                        class RiflemanLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_rifleman";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class RiflemanPrice : A3A_Text
                        {
                            idc = A3A_IDC_RIFLEMANPRICE;
                            style = ST_RIGHT;
                            text = "";
                            font = "RobotoCondensedLight";
                            colorText[] = A3A_COLOR_BUTTON_TEXT_DISABLED; // TODO UI-update: Replace color, needs it's own
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class RiflemanNumber : A3A_Text
                        {
                            idc = A3A_IDC_RIFLEMANNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class RiflemanRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_RIFLEMANSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""rifleman""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class RiflemanAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_RIFLEMANADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""rifleman""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(0 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class SquadleaderLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_squad_leader";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(5 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class SquadleaderPrice : RiflemanPrice
                        {
                            idc = A3A_IDC_SQUADLEADERPRICE;
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(5 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class SquadleaderNumber : A3A_Text
                        {
                            idc = A3A_IDC_SQUADLEADERNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(5 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class SquadleaderRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_SQUADLEADERSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""squadleader""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(5 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class SquadleaderAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_SQUADLEADERADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""squadleader""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(5 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class AutoriflemanLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_autorifleman";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(10 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class AutoriflemanPrice : RiflemanPrice
                        {
                            idc = A3A_IDC_AUTORIFLEMANPRICE;
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(10 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class AutoriflemanNumber : A3A_Text
                        {
                            idc = A3A_IDC_AUTORIFLEMANNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(10 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class AutoriflemanRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_AUTORIFLEMANSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""autorifleman""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(10 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class AutoriflemanAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_AUTORIFLEMANADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""autorifleman""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(10 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class GrenadierLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_grenadier";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GrenadierPrice : RiflemanPrice
                        {
                            idc = A3A_IDC_GRENADIERPRICE;
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GrenadierNumber : A3A_Text
                        {
                            idc = A3A_IDC_GRENADIERNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class GrenadierRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_GRENADIERSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""grenadier""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class GrenadierAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_GRENADIERADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""grenadier""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(15 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class MedicLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_medic";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MedicPrice : RiflemanPrice
                        {
                            idc = A3A_IDC_MEDICPRICE;
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MedicNumber : A3A_Text
                        {
                            idc = A3A_IDC_MEDICNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MedicRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_MEDICSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""medic""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class MedicAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_MEDICADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""medic""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(20 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class MortarLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_mortar";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(25 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MortarPrice : RiflemanPrice
                        {
                            idc = A3A_IDC_MORTARPRICE;
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(25 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MortarNumber : A3A_Text
                        {
                            idc = A3A_IDC_MORTARNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(25 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MortarRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_MORTARSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""mortar""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(25 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class MortarAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_MORTARADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""mortar""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(25 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class MarksmanLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_marksman";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(30 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MarksmanPrice : RiflemanPrice
                        {
                            idc = A3A_IDC_MARKSMANPRICE;
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(30 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MarksmanNumber : A3A_Text
                        {
                            idc = A3A_IDC_MARKSMANNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(30 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class MarksmanRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_MARKSMANSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""marksman""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(30 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class MarksmanAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_MARKSMANADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""marksman""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(30 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class AtLabel : A3A_Text
                        {
                            idc = -1;
                            text = "$STR_antistasi_dialogs_hq_garrisons_at";
                            font = "RobotoCondensedLight";
                            x = QUOTE(0 * GRID_W);
                            y = QUOTE(35 * GRID_H);
                            w = QUOTE(26 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class AtPrice : RiflemanPrice
                        {
                            idc = A3A_IDC_ATPRICE;
                            x = QUOTE(26 * GRID_W);
                            y = QUOTE(35 * GRID_H);
                            w = QUOTE(8 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class AtNumber : A3A_Text
                        {
                            idc = A3A_IDC_ATNUMBER;
                            text = "0";
                            style = ST_RIGHT;
                            font = "RobotoCondensedLight";
                            x = QUOTE(34 * GRID_W);
                            y = QUOTE(35 * GRID_H);
                            w = QUOTE(6 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                        };

                        class AtRemove : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_ATSUBBUTTON;
                            text = "-";
                            onButtonClick = "[""garrisonRemove"",[""at""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(41 * GRID_W);
                            y = QUOTE(35 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };

                        class AtAdd : A3A_ShortcutButton
                        {
                            idc = A3A_IDC_ATADDBUTTON;
                            text = "+";
                            onButtonClick = "[""garrisonAdd"",[""at""]] spawn A3A_fnc_hqDialog";
                            x = QUOTE(46 * GRID_W);
                            y = QUOTE(35 * GRID_H);
                            w = QUOTE(4 * GRID_W);
                            h = QUOTE(4 * GRID_H);
                            size = QUOTE(GUI_TEXT_SIZE_LARGE);
                            class textPos
                            {
                                left = QUOTE(1.5 * GRID_W);
                                right = 0;
                                top = QUOTE(-1 * GRID_H);
                                bottom = 0;
                            };
                        };
                    };
                };

                class RebuildButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_REBUILDGARRISONBUTTON;
                    text = "$STR_antistasi_dialogs_hq_garrisons_rebuild_assets_button";
                    onButtonClick = "hint ""Placeholder\nWill use A3A_fnc_rebuildAssets when merged"""; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(10 * GRID_W);
                    y = QUOTE(60 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class DismissGarrisonButton : A3A_ShortcutButton
                {
                    idc = A3A_IDC_DISMISSGARRISONBUTTON;
                    text = "$STR_antistasi_dialogs_hq_garrisons_dismiss_garrison_button";
                    onButtonClick = "[""dismissGarrison""] spawn A3A_fnc_hqDialog";
                    x = QUOTE(38 * GRID_W);
                    y = QUOTE(60 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };


                // Build / Remove outpost buttons
                class BuildWatchpostButton : A3A_ShortcutButton
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_garrisons_build_watchpost_button";
                    onButtonClick = "[""buildWatchpost""] spawn A3A_fnc_hqDialog"; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(10 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class RemoveWatchpostButton : A3A_ShortcutButton
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_garrisons_remove_watchpost_button";
                    onButtonClick = "[""removeWatchpost""] spawn A3A_fnc_hqDialog"; // TODO UI-update: Replace placeholder when merging
                    x = QUOTE(38 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(22 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

            };
        };

        class MinefieldsTab : A3A_DefaultControlsGroup
        {
            idc = A3A_IDC_HQDIALOGMINEFIELDSTAB;

            class controls
            {
                class DeployMinefieldText : A3A_Text
                {
                    idc = -1;
                    style = ST_CENTER;
                    text = "$STR_antistasi_dialogs_hq_minefields_deploy_minefields_label";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(50 * GRID_W);
                    y = QUOTE(16 * GRID_H);
                    w = QUOTE(60 * GRID_W);
                    h = QUOTE(6 * GRID_H);
                };

                class ApersMinefieldIcon : A3A_Picture
                {
                    idc = -1;
                    text = A3A_Icon_AP_Minefield;
                    x = QUOTE(42 * GRID_W);
                    y = QUOTE(24 * GRID_H);
                    w = QUOTE(28 * GRID_W);
                    h = QUOTE(28 * GRID_H);
                };

                class DeployApersMinefieldButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_minefields_apers_mines_button";
                    onButtonClick = "closeDialog 0;[""APERSMine""] spawn A3A_fnc_mineDialog";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(36 * GRID_W);
                    y = QUOTE(54 * GRID_H);
                    w = QUOTE(40 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class AtMinefieldIcon : A3A_Picture
                {
                    idc = -1;
                    text = A3A_Icon_AT_Minefield;
                    x = QUOTE(90 * GRID_W);
                    y = QUOTE(24 * GRID_H);
                    w = QUOTE(28 * GRID_W);
                    h = QUOTE(28 * GRID_H);
                };


                class DeployAtMinefieldButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_minefields_at_mines_button";
                    onButtonClick = "closeDialog 0; [""ATMine""] spawn A3A_fnc_mineDialog";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(84 * GRID_W);
                    y = QUOTE(54 * GRID_H);
                    w = QUOTE(40 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

                class RemoveMinefieldButton : A3A_Button
                {
                    idc = -1;
                    text = "$STR_antistasi_dialogs_hq_minefields_remove_minefield_button";
                    onButtonClick = "closeDialog 0; [""delete""] spawn A3A_fnc_mineDialog;";
                    sizeEx = QUOTE(GUI_TEXT_SIZE_LARGE);
                    x = QUOTE(52 * GRID_W);
                    y = QUOTE(80 * GRID_H);
                    w = QUOTE(56 * GRID_W);
                    h = QUOTE(12 * GRID_H);
                };

            };
        };

        class BackButton : A3A_BackButton
        {
            idc = A3A_IDC_HQDIALOGBACKBUTTON;
            x = QUOTE(DIALOG_X + DIALOG_W * GRID_W - 12 * GRID_W);
            y = QUOTE(DIALOG_Y - 5 * GRID_H);
        };

        class CloseButton : A3A_CloseButton
        {
            idc = -1;
            x = QUOTE(DIALOG_X + DIALOG_W * GRID_W - 5 * GRID_W);
            y = QUOTE(DIALOG_Y - 5 * GRID_H);
        };
    };
};
