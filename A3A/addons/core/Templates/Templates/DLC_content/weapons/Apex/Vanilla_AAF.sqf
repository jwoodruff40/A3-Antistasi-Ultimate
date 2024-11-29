_sfMGOptics append ["optic_ERCO_blk_F", 2.5];
(_sfLoadoutData get "machineGuns") append [
    ["LMG_03_F", "muzzle_snds_H_MG_khk_F", _sfAccessories, _sfMGOptics, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 5
];
(_sfLoadoutData get "SMGs") append [
     ["SMG_05_F","muzzle_snds_L",_sfAccessories, _sfSMGoptics,["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 1
];

_eliteRifleOptics append ["optic_ERCO_blk_F", 1];
// (_eliteLoadoutData get "marksmanRifles") append [
//     ["srifle_DMR_03_khaki_F", "", "acc_pointer_IR", "optic_AMS_khk",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_03_F", "", "acc_pointer_IR", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_06_olive_F", "", "", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"]
// ]; // Why are Marksman DLC items defined in the Apex file?
_eliteMGOptics append ["optic_ERCO_blk_F", 2];
(_eliteLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", eliteAccessories, _eliteMGOptics, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 5
];
(_eliteLoadoutData get "SMGs") append [
    ["SMG_05_F","", _eliteAccessories, _eliteSMGOptics,["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 3
];

// (_militaryLoadoutData get "marksmanRifles") append [
//     ["srifle_DMR_03_khaki_F", "", "acc_flashlight", "optic_AMS_khk",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_03_F", "", "acc_flashlight", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
//     ["srifle_DMR_06_olive_F", "", "", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"]
// ]; // Why are Marksman DLC items defined in the Apex file?
_militaryMGSights append ["optic_ERCO_blk_F", 1];
(_militaryLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", _militaryAttachment, _militaryMGSights, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 10
];
(_militaryLoadoutData get "SMGs") append [
    ["SMG_05_F","", _militaryAttachment, _militarySMGSight,["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 4
];

(_policeLoadoutData get "SMGs") append [
    ["SMG_05_F","","", _policeSMGSights, ["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 4
];

(_militiaLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", "acc_flashlight", _militiaMGSights, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 14
];
(_militiaLoadoutData get "SMGs") append [
    ["SMG_05_F","","acc_flashlight", _militiaSMGsights, ["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 6
];


