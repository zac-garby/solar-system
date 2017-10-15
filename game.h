//
// Created by Zac G on 08/10/2017.
//

#ifndef SOLAR_SYSTEM_GAME_H
#define SOLAR_SYSTEM_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "scene.h"
#include "planet.h"
#include "spaceship.h"
#include "mainmenu.h"
#include "sidebar.h"

// Forward declare Spaceship and Sidebar, because
// of a circular dependency
class Spaceship;
class Sidebar;
class PlanetRelationships;

#include "planet_relationships.h"

/** class Game : public Scene
 *
 * Game is the scene you'll see most of the time.
 * It is the one where the actual game takes place,
 * i.e. planets are rendered, everything happens.
 */
class Game : public Scene {

    // The milliseconds elapsed since the game started
    unsigned int elapsed = 0;

    // The generated planets
    std::vector<Planet> planets;

    // The planet relationship graph
    PlanetRelationships *relationships;

    // The selected planet. Used for dragging
    // from one planet to another
    Planet *selected = nullptr;

    // The sun's CircleShape instance
    sf::CircleShape sun;

    // The current sidebar instance. Can be any
    // subclass of Sidebar
    Sidebar *sidebar;

    // The line connected the sender to the destination
    // planet on planet drag operations
    sf::RectangleShape dragLine;

    sf::Font font;
    sf::Text yearDisplay;

    // Whether the player is dragging from a planet
    // at the moment
    bool dragging;

    // Some abstractions/helpers
    void mouseDown(sf::Vector2f);
    void mouseUp(sf::Vector2f);
    void selectPlanet(Planet *);
    void positionDragLine(sf::Window*);
    void renderRelationships(sf::RenderWindow*);
    std::vector<Planet*> generatePlanets();

public:
    // Initialises the game's properties.
    // Ensures a valid amount of planets are generated.
    Game();

    Scene *update(float) override;
    void render(sf::RenderWindow*) override;
    Scene *handleEvent(sf::Event*) override;
    void removeSidebar();

    std::tuple<int, int, int> getDate();

    // The spaceships currently flying around.
    std::vector<Spaceship> ships;
};

#endif //SOLAR_SYSTEM_GAME_H
