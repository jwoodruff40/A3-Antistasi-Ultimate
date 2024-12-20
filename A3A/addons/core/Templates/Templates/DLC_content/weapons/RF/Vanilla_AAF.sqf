_sfSMGoptics append ["optic_VRCO_RF", 4];
(_sfLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","muzzle_snds_acp", "acc_flashlight_smg_01", _sfSMGoptics,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 1
];
_sfTlOptics append ["optic_VRCO_RF", 0.5];
_sfRifleOptics append ["optic_VRCO_RF", 1.25];
//////////////////////////////////////////////////////
_eliteSMGOptics append ["optic_VRCO_RF", 5];
(_eliteLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","","acc_flashlight_smg_01", _eliteSMGOptics,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 2.5
];
_eliteSlOptics append ["optic_VRCO_RF", 0.5];
_eliteRifleOptics append ["optic_VRCO_RF", 3.5];
//////////////////////////////////////////////////////
_militarySMGSights append ["optic_VRCO_RF", 3];
(_militaryLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","","acc_flashlight_smg_01", _militarySMGSights,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 2.5
];
_militarySlRifleSights append ["optic_VRCO_RF", 1];
_militaryRifleSights append ["optic_VRCO_RF", 2.5];
//////////////////////////////////////////////////////
(_policeLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","","acc_flashlight_smg_01", _policeSMGSights,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 1.5 
];
//////////////////////////////////////////////////////
(_militiaLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","","acc_flashlight_smg_01", _militiaSMGsights,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 1
];
(_militiaLoadoutData get "marksmanRifles") append [
    ["srifle_h6_digi_rf", "", "", _militiaMarksmanSights,["10Rnd_556x45_AP_Stanag_RF","10Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF"], [], ""], 7.5,
    ["srifle_h6_oli_rf", "", "", _militiaMarksmanSights,["10Rnd_556x45_AP_Stanag_RF","10Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF"], [], ""], 7.5
];
(_militiaLoadoutData get "sniperRifles") append [
    ["srifle_h6_digi_rf", "", "", _militiaSniperSights,["10Rnd_556x45_AP_Stanag_RF","10Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF"], [], ""], 10,
    ["srifle_h6_oli_rf", "", "", _militiaSniperSights,["10Rnd_556x45_AP_Stanag_RF","10Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF","20Rnd_556x45_AP_Stanag_RF"], [], ""], 10
];
//////////////////////////////////////////////////////
_rfSFDeagleSights = ["optic_VRCO_pistol_RF", 8, "optic_rds_RF", 2]; // Better than making variants of each Deagle with different optics and separately balancing their weights.
(_sfLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "muzzle_snds_L", "acc_flashlight_IR_pistol_RF", "optic_MRD_tan_RF", ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF"], [], ""], 2.5,
    ["hgun_Glock19_auto_Tan_RF", "muzzle_snds_L", "acc_flashlight_IR_pistol_RF", "optic_MRD_tan_RF", ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF","65Rnd_9x19_Mag_RF"], [], ""], 7.5,
    ["hgun_DEagle_RF", "", "", _rfSFDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 5, 
    ["hgun_DEagle_classic_RF", "", "", _rfSFDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 2,
    ["hgun_DEagle_copper_RF", "", "", _rfSFDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.5,
    ["hgun_DEagle_bronze_RF", "", "", _rfSFDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 1,
    ["hgun_DEagle_gold_RF", "", "", _rfSFDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.25
    // SpecOps use the Deagle enough where it appears as frequently as other sidearms.
];
_rfEliteDeagleSights = ["optic_VRCO_pistol_RF", 6, "optic_rds_RF", 4];
_rfEliteGlockSights = ["optic_MRD_tan_RF", 3, "", 1];
(_eliteLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "", "acc_flashlight_IR_pistol_RF", _rfEliteGlockSights, ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF"], [], ""], 7,
    ["hgun_Glock19_auto_Tan_RF", "", "acc_flashlight_IR_pistol_RF", _rfEliteGlockSights, ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF","65Rnd_9x19_Mag_RF"], [], ""], 3,
    ["hgun_DEagle_RF", "", "", _rfEliteDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 1,
    ["hgun_DEagle_bronze_RF", "", "", _rfEliteDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.1,
    ["hgun_DEagle_gold_RF", "", "", _rfEliteDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.025,
    ["hgun_DEagle_classic_RF", "", "", _rfEliteDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.25,
    ["hgun_DEagle_copper_RF", "", "", _rfEliteDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.1
    // Elites carry around the Deagle uncommonly, but enough where you should be able to consistently collect them.
];

_rfMilitaryDeagleSights = ["optic_rds_RF", 1, "", 2];
_rfMilitaryGlockSights = ["optic_MRD_tan_RF", 1, "", 3];
(_militaryLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "", "acc_flashlight_pistol", _rfMilitaryGlockSights, ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF"], [], ""], 9,
    ["hgun_Glock19_auto_Tan_RF", "", "acc_flashlight_pistol", _rfMilitaryGlockSights, ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF"], [], ""], 1, // Full auto Glocks aren't something the usual soldier is gonna carry around often.
    ["hgun_DEagle_RF", "", "", _rfMilitaryDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.3,
    ["hgun_DEagle_classic_RF", "", "", _rfMilitaryDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.1,
    ["hgun_DEagle_copper_RF", "", "", _rfMilitaryDeagleSights, ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.1
    // Make the Deagle super rare, since it's an unusual gun for a normal soldier to have.
];
(_militiaLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "", "", "", ["17Rnd_9x19_Mag_RF","17Rnd_9x19_Mag_RF"], [], ""], 10
];

(_policeLoadoutData get "sidearms") append [
    ["hgun_Glock19_RF", "", "", "", ["17Rnd_9x19_Mag_RF","17Rnd_9x19_Mag_RF"], [], ""], 10
];




