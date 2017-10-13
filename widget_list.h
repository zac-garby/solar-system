//
// Created by Zac G on 11/10/2017.
//

#ifndef SOLAR_SYSTEM_WIDGET_LIST_H
#define SOLAR_SYSTEM_WIDGET_LIST_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "widget.h"

class WidgetList {
    std::vector<Widget*> widgets;
    sf::Vector2f next;
    sf::Vector2i mouse;

public:
    WidgetList();
    void addWidget(Widget*);
    void render(sf::RenderWindow*);
    void update(float);
    void handleEvent(sf::Event*);
};

#endif //SOLAR_SYSTEM_WIDGET_LIST_H
