_marksmanRifles pushBack ["srifle_DMR_01_black_RF", "", "acc_flashlight", "optic_VRCO_RF", ["10Rnd_762x54_Mag","10Rnd_762x54_Mag","10Rnd_762x54_Mag"], [], ""];
_rifles pushBack ["arifle_ash12_blk_RF", "", "", "", ["20Rnd_127x55_Mag_RF","20Rnd_127x55_Mag_RF"], [], ""];
_enforcerRifles pushBack ["arifle_ash12_LR_blk_RF", "", "optic_VRCO_RF", "", ["20Rnd_127x55_Mag_RF","20Rnd_127x55_Mag_RF"], [], ""];
_tunedRifles pushBack ["arifle_ash12_LR_blk_RF", "", "", "optic_VRCO_RF", ["20Rnd_127x55_Mag_RF","20Rnd_127x55_Mag_RF"], [], ""];
_gls pushBack ["arifle_ash12_GL_blk_RF", "", "acc_flashlight", "optic_VRCO_khk_RF", ["10Rnd_127x55_Mag_RF", "20Rnd_127x55_Mag_RF"], ["1Rnd_HE_Grenade_shell", "1Rnd_SmokeGreen_Grenade_shell", "UGL_FlareGreen_F"], ""];
_pistols append ["hgun_Glock19_RF", "hgun_Glock19_auto_RF", "hgun_DEagle_RF", "hgun_Glock19_auto_khk_RF", "hgun_DEagle_classic_RF"];

if (random 100 <= 45) then {
	_tunedRifles pushBack ["srifle_h6_gold_rf", "muzzle_snds_M", "", "optic_VRCO_RF", ["30Rnd_556x45_AP_Stanag_green_RF"], [], ""];
	_pistols append ["hgun_DEagle_gold_RF"];
};

_rpgs append [
    ["SPE_M1A1_Bazooka", "", "", "", ["SPE_1Rnd_60mm_M6","SPE_1Rnd_60mm_M6","SPE_1Rnd_60mm_M6"], [], ""]
];
_rifles append [
    ["SPE_STG44","","","",["SPE_30Rnd_792x33","SPE_30Rnd_792x33","SPE_30rnd_792x33_t"],[],""],
    ["SPE_M1918A2_BAR","","","",["SPE_20Rnd_762x63","SPE_20Rnd_762x63_M1","SPE_20Rnd_762x63_M2_AP"],[],""]
];
_marksmanRifles append [
    ["SPE_M1903A3_Springfield","SPE_ACC_M1_Bayo","","",["SPE_5Rnd_762x63","SPE_5Rnd_762x63_M1","SPE_5Rnd_762x63_t","SPE_5Rnd_762x63_M2_AP","SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1903A3_Springfield","SPE_ACC_GL_M1","","",["SPE_5Rnd_762x63","SPE_5Rnd_762x63_M1","SPE_5Rnd_762x63_t","SPE_5Rnd_762x63_M2_AP","SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1903A3_Springfield","SPE_ACC_M1905_Bayo","","",["SPE_5Rnd_762x63","SPE_5Rnd_762x63_M1","SPE_5Rnd_762x63_t","SPE_5Rnd_762x63_M2_AP","SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1903A3_Springfield","","","",["SPE_5Rnd_762x63","SPE_5Rnd_762x63_M1","SPE_5Rnd_762x63_t","SPE_5Rnd_762x63_M2_AP","SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1_Garand","SPE_ACC_M1_Bayo","","",["SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1_Garand","SPE_ACC_M1905_Bayo","","",["SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1_Garand","SPE_ACC_GL_M7","","",["SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1_Garand","","","",["SPE_8Rnd_762x63","SPE_8Rnd_762x63_M1","SPE_8Rnd_762x63_t","SPE_8Rnd_762x63_M2_AP"],[],""],
    ["SPE_K98_Late","SPE_ACC_K98_Bayo","","",["SPE_5Rnd_792x57","SPE_5Rnd_792x57_t","SPE_5Rnd_792x57_SMK","SPE_5Rnd_792x57_sS"],[],""],
    ["SPE_K98","SPE_ACC_K98_Bayo","","",["SPE_5Rnd_792x57","SPE_5Rnd_792x57_t","SPE_5Rnd_792x57_SMK","SPE_5Rnd_792x57_sS"],[],""],
    ["SPE_G43","SPE_ACC_K98_Bayo","","",["SPE_10Rnd_792x57","SPE_10Rnd_792x57_T2","SPE_10Rnd_792x57_SMK","SPE_10Rnd_792x57_sS","SPE_10Rnd_792x57_T"],[],""],
	["SPE_M1903A4_Springfield","","","",["SPE_5Rnd_762x63","SPE_5Rnd_762x63_M1","SPE_5Rnd_762x63_t","SPE_5Rnd_762x63_M2_AP"],[],""],
    ["SPE_K98ZF39","","","",["SPE_5Rnd_792x57","SPE_5Rnd_792x57_t","SPE_5Rnd_792x57_SMK","SPE_5Rnd_792x57_sS"],[],""]
];
_mgs append [
    ["SPE_MG42","","","",["SPE_50Rnd_792x57_SMK","SPE_50Rnd_792x57_SMK","SPE_50Rnd_792x57_sS","SPE_50Rnd_792x57"],[],""],
    ["SPE_MG34","","","",["SPE_50Rnd_792x57_SMK","SPE_50Rnd_792x57_SMK","SPE_50Rnd_792x57_sS","SPE_50Rnd_792x57"],[],""],
    ["SPE_M1919A6","","","",["SPE_100Rnd_762x63","SPE_100Rnd_762x63_M1","SPE_100Rnd_762x63_M2_AP","SPE_50Rnd_762x63_M2_AP"],[],""],
    ["SPE_M1919A4","","","",["SPE_100Rnd_762x63","SPE_100Rnd_762x63_M1","SPE_100Rnd_762x63_M2_AP","SPE_50Rnd_762x63_M2_AP"],[],""],
    ["SPE_FM_24_M29","","","",["SPE_25Rnd_75x54","SPE_25Rnd_75x54","SPE_25Rnd_75x54_35P_AP","SPE_25Rnd_75x54_35P_AP","SPE_25Rnd_75x54","SPE_25Rnd_75x54","SPE_25Rnd_75x54_35P_AP","SPE_25Rnd_75x54_35P_AP"],[],""]
];
_carbines append [
    ["SPE_M1_Carbine","SPE_ACC_GL_M8","","",["SPE_15Rnd_762x33","SPE_15Rnd_762x33","SPE_15Rnd_762x33_t","SPE_15Rnd_762x33_t"], [], ""],
    ["SPE_M1_Carbine","","","",["SPE_15Rnd_762x33","SPE_15Rnd_762x33","SPE_15Rnd_762x33_t","SPE_15Rnd_762x33_t"], [], ""],
    ["SPE_Fusil_Mle_208_12_Sawedoff","","","",["SPE_2Rnd_12x65_No4_Buck","SPE_2Rnd_12x65_Pellets","SPE_2Rnd_12x65_Slug","SPE_2Rnd_12x65_No4_Buck"], [], ""],
    ["SPE_Fusil_Mle_208_12","","","",["SPE_2Rnd_12x65_No4_Buck","SPE_2Rnd_12x65_Pellets","SPE_2Rnd_12x65_Slug","SPE_2Rnd_12x65_No4_Buck"], [], ""]
];
_pistols append [
    ["SPE_M1911","","","",["SPE_7Rnd_45ACP_1911","SPE_7Rnd_45ACP_1911","SPE_7Rnd_45ACP_1911","SPE_7Rnd_45ACP_1911"], [], ""],
    ["SPE_P08","","","",["SPE_8Rnd_9x19_P08","SPE_8Rnd_9x19_P08","SPE_8Rnd_9x19_P08","SPE_8Rnd_9x19_P08"], [], ""]
];