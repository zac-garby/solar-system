//
// Created by Zac G on 08/10/2017.
//

#ifndef SOLAR_SYSTEM_SIDEBAR_H
#define SOLAR_SYSTEM_SIDEBAR_H

#include <SFML/Graphics.hpp>

#include "config.h"
#include "planet.h"
#include "widget.h"
#include "widget_list.h"

class Planet;
class Game;

class Sidebar {
protected:
    sf::RectangleShape background;
    bool mouseDown;
    float mouseX, mouseY;

public:
    virtual void render(sf::RenderWindow *win) { win->draw(background); }
    virtual void update(float dt) {};
    virtual void handleEvent(sf::Event *event) {};
};

class PlanetInspector : public Sidebar {
    sf::Font body, header;
    sf::Text noPlanet;

    TitleWidget title;
    SpaceWidget space;
    WidgetList widgets;

    TextWidget physical, distance, radius, mass, speed,
            life, population, inhabitants,
            resources, metal, populationResource, food, weaponary;

public:
    Planet *planet = nullptr;

    explicit PlanetInspector(Planet*);
    void render(sf::RenderWindow*) override;
};

class ShipDesigner : public Sidebar {
    sf::Font body, header;

    TitleWidget title;
    SpaceWidget space;
    ButtonWidget launch;
    WidgetList widgets;

    SliderWidget metalSlider, populationSlider,
            foodSlider, weaponarySlider;

    TextWidget resourcesHeader, planetsText,
            metal, population, food, weaponary;

public:
    Planet *sender, *destination;

    explicit ShipDesigner(Game*, Planet*, Planet*);
    void render(sf::RenderWindow*) override;
    void update(float dt) override;
    void handleEvent(sf::Event *event) override;

};

#endif //SOLAR_SYSTEM_SIDEBAR_H
