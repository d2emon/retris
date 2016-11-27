#ifndef SETTINGS_HPP_INCLUDED
#define SETTINGS_HPP_INCLUDED

#include <SFML/Graphics.hpp>

sf::String gameTitle = "Retris";
int winSize[2] = {800, 600};

const int M=20;
const int N=10;
int boxSize[2] = {N, M};
int pointSize[2] = {18, 18};

int backgroundsCount = 11;
sf::String backgrounds[11] = {
    "res/background/1.png",
    "res/background/2.png",
    "res/background/3.png",
    "res/background/4.png",
    "res/background/5.png",
    "res/background/6.png",
    "res/background/7.png",
    "res/background/8.png",
    "res/background/9.png",
    "res/background/10.png",
};
sf::String interface = "res/frame.png";

#endif // SETTINGS_HPP_INCLUDED
