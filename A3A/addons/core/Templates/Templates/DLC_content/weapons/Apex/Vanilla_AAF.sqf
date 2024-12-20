_sfMGOptics append ["optic_ERCO_blk_F", 2.5];
_sfTlOptics append  ["optic_ERCO_blk_F", 4];
_sfRifleOptics append  ["optic_ERCO_blk_F", 2.5];
(_sfLoadoutData get "machineGuns") append [
    ["LMG_03_F", "muzzle_snds_H_MG_khk_F", _sfAccessories, _sfMGOptics, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 3
];
(_sfLoadoutData get "SMGs") append [
     ["SMG_05_F","muzzle_snds_L",_sfAccessories, _sfSMGoptics,["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 1
];
//////////////////////////////////////////////////////
_eliteRifleOptics append ["optic_ERCO_blk_F", 1];
_eliteSlOptics append ["optic_ERCO_blk_F", 3];
// (_eliteLoadoutData get "marksmanRifles") append [
//     ["srifle_DMR_03_khaki_F", "", "acc_pointer_IR", "optic_AMS_khk",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_03_F", "", "acc_pointer_IR", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_06_olive_F", "", "", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"]
// ]; // Why are Marksman DLC items defined in the Apex file?
_eliteMGOptics append ["optic_ERCO_blk_F", 2];
(_eliteLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", _eliteAccessories, _eliteMGOptics, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 2
];
(_eliteLoadoutData get "SMGs") append [
    ["SMG_05_F","", _eliteAccessories, _eliteSMGOptics,["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 1
];
//////////////////////////////////////////////////////
// (_militaryLoadoutData get "marksmanRifles") append [
//     ["srifle_DMR_03_khaki_F", "", "acc_flashlight", "optic_AMS_khk",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_03_F", "", "acc_flashlight", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_06_olive_F", "", "", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"]
// ]; // Why are Marksman DLC items defined in the Apex file?
_militaryMGSights append ["optic_ERCO_blk_F", 1];
_militaryRifleSights append ["optic_ERCO_blk_F", 0.5];
_militarySlRifleSights append ["optic_ERCO_blk_F", 1.5];
(_militaryLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", _militaryAttachments, _militaryMGSights, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 7.5
];
(_militaryLoadoutData get "SMGs") append [
    ["SMG_05_F","", _militaryAttachments, _militarySMGSight,["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 4
];
//////////////////////////////////////////////////////
(_policeLoadoutData get "SMGs") append [
    ["SMG_05_F","","", _policeSMGSights, ["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 6
];
//////////////////////////////////////////////////////
(_militiaLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", _militiaAttachments, _militiaMGSights, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 14
];
(_militiaLoadoutData get "SMGs") append [
    ["SMG_05_F","",_militiaAttachments, _militiaSMGsights, ["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 7.5
];


