//
// Created by Zac G on 11/10/2017.
//

#ifndef SOLAR_SYSTEM_WIDGET_LIST_H
#define SOLAR_SYSTEM_WIDGET_LIST_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "widget.h"

class WidgetList {
    // The contained widgets
    std::vector<Widget*> widgets;

    // The next widget position, updated for every widget
    // added
    sf::Vector2f next;

    // The current mouse position
    sf::Vector2i mouse;

public:
    WidgetList();

    // Adds a widget to the list
    void addWidget(Widget*);

    // Renders the widgets on the given window
    void render(sf::RenderWindow*);

    // Updates the widgets by the given delta time
    void update(float);

    // Sends the event to all widgets
    void handleEvent(sf::Event*);
};

#endif //SOLAR_SYSTEM_WIDGET_LIST_H
