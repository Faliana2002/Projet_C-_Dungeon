#ifndef DECLARATION
#define DECLARATION

#include <string>

std::string reference  = "../0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7/frames/";
std::string idle = "_idle_anim_f";
std::string run = "_run_anim_f";
std::string fin_str = ".png";

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
                            "big_demon",
                            "big_zombie",
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
                            "wogol"};       //16
// Par 4 (au lieu de 8) : zombie/slug/tiny_slug/ice_zombie/muddy/necromancer/swampy/

int width = 1280;
int height = 720;

#endif