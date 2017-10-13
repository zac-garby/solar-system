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

class Spaceship;
class Sidebar;

class Game : public Scene {
    std::vector<Planet> planets;
    Planet *selected = nullptr;
    sf::CircleShape sun;
    Sidebar *sidebar;
    sf::RectangleShape dragLine;
    bool dragging;

    void mouseDown(sf::Vector2f);
    void mouseUp(sf::Vector2f);
    void selectPlanet(Planet *);
    void positionDragLine(sf::Window*);

public:
    Game();

    Scene *update(float) override;
    void render(sf::RenderWindow*) override;
    Scene *handleEvent(sf::Event*) override;
    void removeSidebar();

    std::vector<Spaceship> ships;
};

#endif //SOLAR_SYSTEM_GAME_H
