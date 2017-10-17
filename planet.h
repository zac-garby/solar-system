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
#include <math.h>

#include "config.h"
#include "resource.h"
#include "spaceship.h"
#include "game.h"

class Game;

class Planet {
    const int foodCap = 50000;
    const int farmersCap = 5000000;

    sf::CircleShape shape;
    sf::CircleShape orbit;
    sf::CircleShape border;

    // The ships ready to be launched. This is necessary
    // because the Game instance isn't accessable from launchShip(),
    // so update() iterates this queue and launches all the ships in it.
    std::vector<Spaceship> shipQueue;

public:
    // The planet's name
    std::string name;

    // The planet's colour
    sf::Color colour;

    // The planet's resource store
    Resources resources;

    // The properties. This might be moved to its own struct
    // in the future.
    float earthLikeness;    // How likely the planet is to Earth (1f == Earth)
    float radius;           // x10^2AU
    float distanceFromSun;  // miles
    float mass;             // yg (yottagrams)
    float angle;            // º
    float speed;            // px/s
    float biodiversity;	    // between 1-10
    float capacity;         // capacity
    float gravity;          // relative to Earth's g

    // Explicit since there's only one parameter.
    explicit Planet(float radius);

    void render(sf::RenderWindow*);
    void renderOrbit(sf::RenderWindow*);
    void renderBorder(sf::RenderWindow*);
    void update(Game*, float dt);

    // Calculates the planet's radius in pixels
    float getPixelRadius();

    // Calculates the planet border's radius in pixels
    float getBorderPixelRadius();

    // Checks whether the given vector is inside
    // the planet's bounds
    bool contains(sf::Vector2f);

    // Launches a ship from this planet with the
    // given resources, towards the specified planet.
    void launchShip(Resources, Planet*);

    // Gets the current position relative to the
    // parameter.
    sf::Vector2f getPosition(sf::Vector2f);

    // Generates the name of the inhabitants. It is
    // determinate (i.e. not random,) but if it was,
    // a few things would have to change.
    std::string getInhabitantName();

    // Generates a random planet name.
    static std::string randomName();

    // A planet can be inhabitet/uninhabited.
    bool isInhabited();
};

#endif //SOLAR_SYSTEM_PLANET_H
