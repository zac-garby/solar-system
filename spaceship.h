//
// Created by Zac G on 10/10/2017.
//

#ifndef SOLAR_SYSTEM_SPACESHIP_H
#define SOLAR_SYSTEM_SPACESHIP_H

#include <SFML/Graphics.hpp>

#include "config.h"
#include "planet.h"
#include "resource.h"

// Forward declaration of Planet
class Planet;

class Spaceship {
    sf::CircleShape shape;
    Planet *sender, *destination;
    sf::Vector2f position, velocity;

    sf::Vector2f getDirectionToDestination();
    bool hasReachedDestination();

public:
    Spaceship(Planet*, Planet*, Resources);
    void update(float);
    void render(sf::RenderWindow*);

    unsigned int id;
    bool delivered;
    Resources resources;

    static unsigned int nextID;
};

#endif //SOLAR_SYSTEM_SPACESHIP_H
