//
// Created by Zac G on 08/10/2017.
//

#ifndef SOLAR_SYSTEM_PLANET_H
#define SOLAR_SYSTEM_PLANET_H

#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <vector>
#include <iostream>

#include "config.h"
#include "resource.h"
#include "spaceship.h"
#include "game.h"

class Game;

class Planet {
    sf::CircleShape shape;
    sf::CircleShape orbit;

    std::vector<Spaceship> shipQueue;

public:
    std::string name;
    sf::Color colour;
    Resources resources;

    float radius;           // x10^2AU
    float distanceFromSun;  // miles
    float mass;             // yg (yottagrams)
    float angle;            // º
    float speed;            // px/s

    explicit Planet(float);
    void render(sf::RenderWindow*);
    void renderOrbit(sf::RenderWindow*);
    void update(Game*, float);
    float getPixelRadius();
    bool contains(sf::Vector2f);
    void launchShip(Resources, Planet*);
    sf::Vector2f getPosition(sf::Vector2f);
    std::string getInhabitantName();

    static std::string randomName();
};

#endif //SOLAR_SYSTEM_PLANET_H
