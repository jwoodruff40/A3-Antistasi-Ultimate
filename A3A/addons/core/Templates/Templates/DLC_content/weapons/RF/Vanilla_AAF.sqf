_sfSMGoptics append ["optic_VRCO_RF", 4];
(_sfLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","muzzle_snds_acp", "acc_flashlight_smg_01", _sfSMGoptics,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 1
];
_sfTlOptics append ["optic_VRCO_RF", 0.5];
_sfRifleOptics append ["optic_VRCO_RF", 1.25];

_eliteSMGOptics append ["optic_VRCO_RF", 5];
(_eliteLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","","acc_flashlight_smg_01", _eliteSMGOptic,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 2.5,
];
_eliteSlOptics append ["optic_VRCO_RF", 0.5];
_eliteRifleOptics append ["optic_VRCO_RF", 3.5];


_militarySMGSights append ["optic_VRCO_RF", 3];
(_militaryLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","","acc_flashlight_smg_01", _militarySMGSights,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 2.5
];
_militarySlRifleSights append ["optic_VRCO_RF", 1];
_militaryRifleSights append ["optic_VRCO_RF", 1];

(_policeLoadoutData get "SMGs") append [
    ["SMG_01_black_RF","","acc_flashlight_smg_01", _policeSMGSights,["30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01","30Rnd_45ACP_Mag_SMG_01_Tracer_Green"], [], ""], 1.5 
];

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

(_sfLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "muzzle_snds_L", "acc_flashlight_IR_pistol_RF", "optic_MRD_tan_RF", ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF"], [], ""], 2.5
    ["hgun_Glock19_auto_Tan_RF", "muzzle_snds_L", "acc_flashlight_IR_pistol_RF", "optic_MRD_tan_RF", ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF","65Rnd_9x19_Mag_RF"], [], ""], 7.5,
    ["hgun_DEagle_RF", "", "", "optic_VRCO_pistol_RF", ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 5, // SpecOps use the Deagle enough where it appears as frequently as other sidearms.
    ["hgun_DEagle_classic_RF", "", "", "optic_VRCO_pistol_RF", ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 2.5,
    ["hgun_DEagle_copper_RF", "", "", "optic_VRCO_pistol_RF", ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 2.5
];
(_eliteLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "", "acc_flashlight_IR_pistol_RF", "optic_MRD_tan_RF", ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF"], [], ""], 5,
    ["hgun_Glock19_auto_Tan_RF", "", "acc_flashlight_IR_pistol_RF", "optic_MRD_tan_RF", ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF","65Rnd_9x19_Mag_RF"], [], ""], 5,
    ["hgun_DEagle_RF", "", "", "optic_VRCO_pistol_RF", ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 5
];
(_militaryLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "", "acc_flashlight_pistol", "optic_MRD_tan_RF", ["17Rnd_9x19_Mag_RF","33Rnd_9x19_Mag_RF"], [], ""], 10,
    ["hgun_DEagle_RF", "", "", "optic_VRCO_pistol_RF", ["7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF","7Rnd_50AE_Mag_RF"], [], ""], 0.5 // Make it super rare, since it's an unusual gun for a normal soldier to have.
];
(_militiaLoadoutData get "sidearms") append [
    ["hgun_Glock19_Tan_RF", "", "", "", ["17Rnd_9x19_Mag_RF","17Rnd_9x19_Mag_RF"], [], ""], 10
];

(_policeLoadoutData get "sidearms") append [
    ["hgun_Glock19_RF", "", "", "", ["17Rnd_9x19_Mag_RF","17Rnd_9x19_Mag_RF"], [], ""], 10
];




