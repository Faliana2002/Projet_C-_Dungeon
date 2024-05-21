#ifndef MAPDECLARATION
#define MAPDECLARATION

#include <vector>
#include <string>
#include "../point.hpp"
#include "../rectangle.hpp"

std::vector<Point> contourList1 = {Point(384,0),Point(432,0),Point(432,96),Point(1104,96),Point(1104,192),Point(1280,192),Point(1280,336),Point(1152,336),Point(1152,528),Point(1200,528),Point(1200,576),Point(1152,576),Point(1152,672),Point(624,672),Point(624,576),Point(528,576),Point(528,672),Point(480,672),Point(480,576),Point(384,576),Point(384,672),Point(144,672),Point(144,576),Point(336,576),Point(336,480),Point(144,480),Point(144,384),Point(240,384),Point(240,288),Point(144,288),Point(144,96),Point(288,96),Point(288,48),Point(336,48),Point(336,0),Point(384,0)};
std::vector<Rectangle> obstacleList1 = {Rectangle(Point(144,288), 96, 96),Rectangle(Point(480,144), 96, 96),Rectangle(Point(480,240), 96, 96),Rectangle(Point(336,384), 96, 96),Rectangle(Point(432,432), 96, 96),Rectangle(Point(528,144), 96, 96),Rectangle(Point(768,288), 96, 96),Rectangle(Point(816,384), 96, 96),Rectangle(Point(720,480), 96, 96),Rectangle(Point(816,528), 96, 96)};
std::string nom1 = "map1.png";
std::vector<Point> ES1 = {Point(432, 0), Point(1200, 240)};

std::vector<Point> contourList2 = {Point(0,192),Point(288,192),Point(288,96),Point(864,96),Point(868,192),Point(960,192),Point(960,96),Point(1008,96),Point(1008,384),Point(1104,384),Point(1104,336),Point(1152,336),Point(1152,384),Point(1296,384),Point(1296,528),Point(624,528),Point(624,432),Point(528,432),Point(582,528),Point(288,528),Point(288,336),Point(0,336),Point(0, 196)};
std::vector<Rectangle> obstacleList2 = {Rectangle(Point(672,240),96,96)};
std::string nom2 = "map2.png";
std::vector<Point> ES2 = {Point(0, 0240), Point(1200, 432)};

std::vector<Point> contourList3 = {Point(0, 384),Point(96,384),Point(96,192),Point(192,192),Point(192,288),Point(288,288),Point(288,192),Point(816,192),Point(816,0),Point(960,0),Point(960,288),Point(1056,288),Point(1056,192),Point(1152,192),Point(1152,336),Point(1056,336),Point(1056,432),Point(1153,432),Point(1152,624),Point(768,624),Point(768,672),Point(720,672),Point(720,624),Point(240,624),Point(240,528),Point(144,528),Point(144,624),Point(96,624),Point(96,528),Point(0,528),Point(0,384)};
std::vector<Rectangle> obstacleList3 = {Rectangle(Point(336,240), 96, 96), Rectangle(Point(528,240), 96, 96), Rectangle(Point(672,432), 96, 96), Rectangle(Point(912,336), 96, 96)};
std::string nom3 = "map3.png";
std::vector<Point> ES3 = {Point(0, 432), Point(864, 10)};

#endif