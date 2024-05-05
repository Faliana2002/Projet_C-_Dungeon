#ifndef DECLARATION
#define DECLARATION

#include <string>

std::string reference  = "../0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7/frames/";
std::string idle = "_idle_anim_f";
std::string run = "_run_anim_f";
std::string fin_str = ".png";
std::string weapon_str = "weapon_";
std::string wall_edge_str = "wall_egde_";
std::string fountain_anim_str1 = "wall_fountain_";
std::string fountain_anim_str2 = "anim_f_";
std::string floor_str = "floor_";
std::string spikes_anim_str = "_anim_f";

int nbLJoueur = 9;
int nbLEnnemi = 16;

std::string listeJoueurs[] = {"angel",
                            //"big_demon",
                            //"big_zombie",
                            //"chort",
                            //"doc",
                            "dwarf_f",
                            "dwarf_m",
                            "elf_f",
                            "elf_m",
                            //"goblin",
                            //"imp",
                            "knight_f",
                            "knight_m",
                            //"lizard_f",
                            //"lizard_m",
                            //"masked_orc",
                            //"ogre",
                            //"orc_shaman",
                            //"orc_warrior",
                            //"pumpkin_dude",
                            //"skelet",
                            //"tiny_zombie",
                            "wizzard_f",
                            "wizzard_m"};   // 9
                            //"wogol"};       //25

std::string listeEnnemi[] = {//"angel",
                            //"big_demon",
                            //"big_zombie",
                            "chort",
                            "doc",
                            //"dwarf_f",
                            //"dwarf_m",
                            //"elf_f",
                            //"elf_m",
                            "goblin",
                            "imp",
                            //"knight_f",
                            //"knight_m",
                            "lizard_f",
                            "lizard_m",
                            "masked_orc",
                            "ogre",
                            "orc_shaman",
                            "orc_warrior",
                            "pumpkin_dude",
                            "skelet",
                            "tiny_zombie",
                            //"wizzard_f",
                            //"wizzard_m",
                            "wogol"};       //14
// Par 4 (au lieu de 8) : zombie/slug/tiny_slug/ice_zombie/muddy/necromancer/swampy/

std::string listeArmesCAC[] = {"anime_sword",
                              "axe",
                              "baton_with_spikes",
                              "big_hamme",
                              "cleaver",
                              "double_axe",
                              "duel_sword",
                              "golden_sword",
                              "hammer",
                              "katana",
                              "knife",
                              "knight_sword",
                              "lavish_sword",
                              "mace",
                              "machete",
                              "red_gem_sword",
                              "regular_sword",
                              "rusty_sword",
                              "saw_sword",
                              "spear",
                              "throwing_axe",
                              "waraxe"};

std::string listeArmesDistance[] = {"bow",
                                    "bow_2",
                                    "green_magic_staff",
                                    "red_magic_staff"};

std::string arrowFile = "arrow";

//std::map<string, string>
std::string listeWallsEdge[] = {"bottom_left",
                                "bottom_right",
                                "left",
                                "mid_left",
                                "mid_right",
                                "right",
                                "top_left",
                                "top_right",
                                "tshape_bottom_left",
                                "tshape_bottom_right",
                                "tshape_left",
                                "tshape_right"};

std::string listeWallsFountainAnim[] = {"bassin_blue",
                                    "bassin_red",
                                    "mid_blue",
                                    "mid_red"};

std::string listeWallsOther[] = {"fountain_top_1",
                                 "fountain_top_2",
                                 "fountain_top_3",
                                 "goo",
                                 "goo_base",
                                 "hole_1",
                                 "hole_2",
                                 "left",
                                 "mid",
                                 "outer_front_left",
                                 "outer_front_right",
                                 "outer_mid_left",
                                 "outer_mid_right",
                                 "outer_top_left",
                                 "outer_top_right",
                                 "right",
                                 "top_left",
                                 "top_mid",
                                 "top_right"};

std::string listeFloor[] = {"_1",
                            "_2",
                            "_3",
                            "_4",
                            "_5",
                            "_6",
                            "_7",
                            "_8",
                            "ladder",
                            "stairs"};

std::string spikes_anim = "spikes"

/*
bombe
bouton
door
chest
crate
column
lever
skull
hear
*/

int width = 1280;
int height = 720;

float alea_mvt_max = 0.1;



#endif