_sfMGOptics append ["optic_ERCO_blk_F", 2.5];
(_sfLoadoutData get "machineGuns") append [
    ["LMG_03_F", "muzzle_snds_H_MG_khk_F", _sfAccessories, _sfMGOptics, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 1
];
(_sfLoadoutData get "SMGs") append [
     ["SMG_05_F","muzzle_snds_L",_sfAccessories,"optic_Holosight_smg_blk_F",["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 1
];

_eliteRifleOptics append ["optic_ERCO_blk_F", 1];
_eliteMGOptics append ["optic_ERCO_blk_F", 2];
(_eliteLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", eliteAccessories, _eliteMGOptics, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 8
];
(_eliteLoadoutData get "SMGs") append [
    ["SMG_05_F","", _eliteAccessories, _eliteSMGoptic,["30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02","30Rnd_9x21_Mag_SMG_02_Tracer_Green"], [], ""], 3
];

_militaryMGSights append ["optic_ERCO_blk_F", 1];
(_militaryLoadoutData get "machineGuns") append [
    ["LMG_03_F", "", _militaryAttachment, `_militaryMGSights`, ["200Rnd_556x45_Box_F", "200Rnd_556x45_Box_F", "200Rnd_556x45_Box_Tracer_F"], [], ""], 10
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


