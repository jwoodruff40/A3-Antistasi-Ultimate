_sfMarksmanOptics append ["optic_AMS", 2];
(_sfLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_03_khaki_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 10,
    ["srifle_DMR_03_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 10,
    // 2:1 ratio of SIGs to MK14s now.
    ["srifle_DMR_06_olive_F", "", "", _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 5
    // The standard M14 shouldn't be appearing that frequently now.
];
_sfSniperOptics append ["optic_AMS", 2, "optic_KHS_blk", 4];
(_sfLoadoutData get "machineGuns") append [
    ["MMG_02_black_F", "muzzle_snds_338_green", _sfAccessories, _sfMGOptics, ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"], 10
];
//////////////////////////////////////////////////////
_eliteMarksmanOptics append ["optic_AMS", 3];
(_eliteLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_03_khaki_F", "", _eliteAccessories, _eliteMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 5, 
    ["srifle_DMR_03_F", "", _eliteAccessories, _eliteMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 5 
    // SIGs now start appearing in even numbers to Mk14s.
    ["srifle_DMR_06_olive_F", "", "", _eliteMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 5
    // The standard M14 shouldn't be appearing that frequently now.
];
_eliteSniperOptics append ["optic_AMS", 2, "optic_KHS_blk", 3];
(_eliteLoadoutData get "machineGuns") append [
    ["MMG_02_black_F", "", _eliteAccessories, _eliteMGOptics, ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"], 10
];
//////////////////////////////////////////////////////
_militaryMarksmanSights append ["optic_AMS", 1];
(_militaryLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_06_camo_F", "", "", _militaryMarksmanSights, [], [], ""],3.5,
    ["srifle_DMR_06_olive_F", "", "", _militaryMarksmanSights, [], [], ""], 3.5
];
_militarySniperSights append ["optic_AMS", 6, "optic_KHS_blk", 5];
//////////////////////////////////////////////////////
(_militiaLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_06_olive_F", "", "", _militiaMarksmanSights, [], [], ""], 15
];
(_militiaLoadoutData get "sniperRifles") append [
    ["srifle_DMR_06_olive_F", "", "", _militiaSniperSights, [], [], ""], 15
];





