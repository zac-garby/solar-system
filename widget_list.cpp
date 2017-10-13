//
// Created by Zac G on 11/10/2017.
//

#include "widget_list.h"

WidgetList::WidgetList() {
    next = sf::Vector2f(WIDGET_MARGIN, WIDGET_MARGIN);
}

void WidgetList::addWidget(Widget *widget) {
    widget->setPosition(next.x, next.y);
    next.y += widget->getHeight() + WIDGET_PADDING;
    widgets.push_back(widget);
}

void WidgetList::render(sf::RenderWindow *win) {
    for (auto &widget : widgets) {
        widget->render(win);
    }

    mouse = sf::Mouse::getPosition(*win);
}

void WidgetList::update(float dt) {
    bool down = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    for (auto &widget : widgets) {
        widget->update(dt, down, mouse.x, mouse.y);
    }
}

void WidgetList::handleEvent(sf::Event *event) {
    for (auto &widget : widgets) {
        widget->handleEvent(event);
    }
}
