#ifndef DECLARATION
#define DECLARATION

#include <string>
#include <vector>
#include <tuple>

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
int nbLEnnemi = 17;
int nbArmesCAC = 22;
int nbJoueur = 3;

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
                            "wogol",
                            "robot"};       //14
// Par 4 (au lieu de 8) : zombie/slug/tiny_slug/ice_zombie/muddy/necromancer/swampy/

// nom, rate_min, rate_max, degats_min, degats_max, d_min, d_max
std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesCAC = {
    std::make_tuple("anime_sword", 2,4,2,5, 50, 70),
    std::make_tuple("axe", 1,2,3,6, 100, 230),
    std::make_tuple("baton_with_spikes", 2,3,2,4,80,160),
    std::make_tuple("big_hammer", 1,1,5,6,150,220),
    std::make_tuple("cleaver", 0,0,0,0,0,0),
    std::make_tuple("double_axe", 0,0,0,0,0,0),
    std::make_tuple("duel_sword", 0,0,0,0,0,0),
    std::make_tuple("golden_sword", 0,0,0,0,0,0),
    std::make_tuple("hammer", 0,0,0,0,0,0),
    std::make_tuple("katana", 0,0,0,0,0,0),
    std::make_tuple("knife", 0,0,0,0,0,0),
    std::make_tuple("knight_sword", 0,0,0,0,0,0),
    std::make_tuple("lavish_sword", 0,0,0,0,0,0),
    std::make_tuple("mace", 0,0,0,0,0,0),
    std::make_tuple("machete", 0,0,0,0,0,0),
    std::make_tuple("red_gem_sword", 0,0,0,0,0,0),
    std::make_tuple("regular_sword", 0,0,0,0,0,0),
    std::make_tuple("rusty_sword", 0,0,0,0,0,0),
    std::make_tuple("saw_sword", 0,0,0,0,0,0),
    std::make_tuple("spear_sword", 0,0,0,0,0,0),
    std::make_tuple("throwing_axe", 0,0,0,0,0,0),
    std::make_tuple("waraxe", 0,0,0,0,0,0)
};

// nom, rate_min, rate_max, degats_min, degats_max, d_min, d_max
std::vector<std::tuple<std::string, float, float, float, float, float, float>> listeArmesDistance = {
    std::make_tuple("bow", 2,4,2,5, 128, 192),
    std::make_tuple("bow_2", 0,0,0,0,0,0),
    std::make_tuple("green_magic_staff", 0,0,0,0,0,0),
    std::make_tuple("red_magic_staff", 0,0,0,0,0,0),
};

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

std::string spikes_anim = "spikes";

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

// Haut, bas, gauche, droite, ramasser/jeter armes attaquer
int toucheJoueur[3][6] = {
    {sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::O, sf::Keyboard::U},
    {sf::Keyboard::Z, sf::Keyboard::S, sf::Keyboard::Q, sf::Keyboard::D, sf::Keyboard::E, sf::Keyboard::A},
    {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::RShift, sf::Keyboard::Numpad0}
};


#endif