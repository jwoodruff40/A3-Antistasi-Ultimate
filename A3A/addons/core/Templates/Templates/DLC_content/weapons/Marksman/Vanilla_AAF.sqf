_sfMarksmanOptics append ["optic_AMS", 2];
(_sfLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_03_khaki_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 7,
    ["srifle_DMR_03_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 7,
    ["srifle_DMR_03_multicam_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 3,
    ["srifle_DMR_03_woodland_F", "muzzle_snds_B", _sfAccessories, _sfMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 3
    // 2:1 ratio of SIGs to MK14s now.
];
_sfSniperOptics append ["optic_AMS", 2, "optic_KHS_blk", 4];
(_sfLoadoutData get "machineGuns") append [
    ["MMG_02_black_F", "muzzle_snds_338_green", _sfAccessories, _sfMGOptics, ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"], 10
];

_eliteMarksmanOptics append ["optic_AMS", 3];
(_eliteLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_03_khaki_F", "", _eliteAccessories, _eliteMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 5, 
    ["srifle_DMR_03_F", "", _eliteAccessories, _eliteMarksmanOptics,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 5 
    // SIGs now start appearing in even numbers to Mk14s.
];
_eliteSniperOptics append ["optic_AMS", 2, "optic_KHS_blk", 3];
(_eliteLoadoutData get "machineGuns") append [
    ["MMG_02_black_F", "", _eliteAccessories, _eliteMGOptics, ["130Rnd_338_Mag", "130Rnd_338_Mag", "130Rnd_338_Mag"], [], "bipod_03_F_blk"], 10
];

_militaryMarksmanSights append ["optic_AMS", 1];
(_militaryLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_03_khaki_F", "", _militaryAttachment, _militaryMarksmanSights,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 1.75
    ["srifle_DMR_03_F", "", _militaryAttachment, _militaryMarksmanSights,["20Rnd_762x51_Mag","20Rnd_762x51_Mag","20Rnd_762x51_Mag"], [], "bipod_03_F_blk"], 1.75 
    // Should be a 4:1 ratio of Mk14s to SIG 556s.
];
_militarySniperSights append ["optic_AMS", 6, "optic_KHS_blk", 5];

(_militiaLoadoutData get "marksmanRifles") append [
    ["srifle_DMR_06_camo_F", "", "", _militiaMarksmanSights, [], [], ""], 7.5,
    ["srifle_DMR_06_olive_F", "", "", _militiaMarksmanSights, [], [], ""], 7.5
];
(_militiaLoadoutData get "sniperRifles") append [
    ["srifle_DMR_06_camo_F", "", "", _militiaSniperSights, [], [], ""], 7.5,
    ["srifle_DMR_06_olive_F", "", "", _militiaSniperSights, [], [], ""], 7.5
];





