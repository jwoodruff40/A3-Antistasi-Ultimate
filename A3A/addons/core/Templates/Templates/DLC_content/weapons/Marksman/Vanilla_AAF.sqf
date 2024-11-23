_sfMarksmanOptics append ["optic_AMS", 3];
(_sfLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_03_khaki_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 1,
    ["srifle_DMR_03_multicam_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 1,
    ["srifle_DMR_03_woodland_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 1,
    ["srifle_DMR_03_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 4,
    ["srifle_DMR_06_olive_F", "muzzle_snds_B", "", _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 0.5,
    ["srifle_DMR_06_camo_F", "muzzle_snds_B", "", _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 1
];
(_sfLoadoutData get "machineGuns") append [
    ["MMG_02_black_F", "muzzle_snds_338_green", _sfAccessories, _sfMGOptics, ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"], 2
];

(_eliteLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_03_khaki_F", "", "acc_pointer_IR", "optic_AMS_khk",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
    ["srifle_DMR_03_F", "", "acc_pointer_IR", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"],
    ["srifle_DMR_06_olive_F", "", "", "optic_AMS",["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"]
];
(_eliteLoadoutData get "machineGuns") append [
    ["MMG_02_black_F", "", "acc_pointer_IR", "optic_Holosight_blk_F", ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"],
    ["MMG_02_black_F", "", "acc_pointer_IR", "optic_MRCO", ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"],
    ["MMG_02_black_F", "", "acc_pointer_IR", "optic_Hamr", ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"],
    ["MMG_02_black_F", "", "acc_pointer_IR", "optic_NVS", ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"]
];

(_militaryLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_06_camo_F", "", "", "optic_SOS", [], [], ""],
    ["srifle_DMR_06_olive_F", "", "", "optic_Hamr", [], [], ""]
];

(_militiaLoadoutData get "marksmanRifles") append [["srifle_DMR_06_olive_F", "", "", "optic_MRCO", [], [], ""]];
(_militiaLoadoutData get "sniperRifles") append [["srifle_DMR_06_olive_F", "", "", "optic_SOS", [], [], ""]];






