    // ***************************** Phalanx Downfall *****************************

    class ACM_PD_Base
    {
        requiredAddons[] = {"gm_weapons_items","Phalanx Downfall"};
        basepath = QPATHTOFOLDER(Templates\Templates\ACM\PD);
        logo = "\gm\gm_core\data\logos\gm_logo_ca.paa";
        maps[] = {"altis", "malden"};
        climate[] = {"arid"};
        priority = 80;
        equipFlags[] = {"specialGM"};
        forceDLC[] = {"gm"};
    };

    class ACM_PD_AAF : ACM_PD_Base
    {
        side = "Occ";
        flagTexture = "a3\data_f\flags\flag_aaf_co.paa";
        name = "[PD] AAF";
        file = "ACM_PD_AI_AAF";
    };

    class ACM_PD_Reb_FIA : ACM_PD_Base
    {
        side = "Reb";
        flagTexture = "a3\data_f\flags\flag_fia_co.paa";
        name = "[PD] FIA";
        file = "ACM_PD_Reb_FIA";
        description = "The Freedom and Independence Army, referred to as the FIA, is the united political front for various anti-Akhanteros political factions.";
    };

    class ACM_PD_Riv_Akh : ACM_PD_Base
    {
        side = "Riv";
        flagTexture = "x\ACM_AAF_2015_core\factions\akhanterite_flag_co.paa";
        name = "[PD] Akhanterites";
        file = "ACM_PD_Riv_Akh";
        description = "A paramilitary structure separate to the AAF only loyal (at least in theory) to their patron, Col. Akhanteros.";
    };

    class ACM_PD_Riv_FIA_GP : ACM_PD_Base
    {
        side = "Riv";
        flagTexture = "x\ACM_AAF_2015_core\factions\GoldenPath_flag_co.paa";
        name = "[PD] FIA Golden Path";
        file = "ACM_PD_Riv_FIA_GP";
        description = "Agrarian communists who have singlehandedly delegitimized the Altian Left.";
    };
    
    class ACM_PD_Riv_FIA_Ins : ACM_PD_Base
    {
        side = "Riv";
        flagTexture = "a3\data_f\flags\flag_fia_co.paa";
        name = "[PD] FIA Insurgents";
        file = "ACM_PD_Riv_FIA_Ins";
        description = "Insurgent groups who conduct assasinations, bombing campaigns, theft, and psychological operations.";
    };

    class ACM_PD_Riv_FIA_Loy : ACM_PD_Base
    {
        side = "Riv";
        flagTexture = QPATHTOFOLDER(Templates\Templates\Vanilla\flags\flag_aaf_torn_co.paa);
        name = "[PD] FIA Loyalists";
        file = "ACM_PD_Riv_FIA_Loy";
        description = "Remnants of the previous Altian government & its armed forces.";
    };

    // ***************************** Griffin's Ascent *****************************
    // Placeholder