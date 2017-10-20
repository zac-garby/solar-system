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
    const long foodCap = 50000;
    const long farmersCap = 5000000;
    const long metalCap = 50000000;
    const long woodCap = 50000000;
    const long waterCap = 50000000;
    const long speciesCap = 500000;
    
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
    float orbitalPeriod;    // in time increments, should be calculated by Kepler's Third Law using distanceFromSun
    float mass;             // yg (yottagrams)
    float angle;            // º
    float speed;            // px/s, calculated from Kepler's Second Law using distanceFromSun
    float biodiversity;	    // between 1-10
    float capacity;         // capacity
    float gravity;          // relative to Earth's g
    float airPressureSurface; // relative to Earth's atm, at surface
    float atmosphereHeight; // in miles, pressure drops linearly to 0 at altitude==atmosphereHeight
    float albedo;           // between 0 and 1
    float surfaceTempEquator; // function of albedo, distanceFromSun
    int moons;              // larger planets tend to have more
    int rings;              // 0 for none, else display n rings as concentric circles above equator

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
