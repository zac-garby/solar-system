//
// Created by Zac G on 11/10/2017.
//

#ifndef SOLAR_SYSTEM_WIDGET_H
#define SOLAR_SYSTEM_WIDGET_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>
#include <iostream>

#include "config.h"

/** class Widget
 *
 * The Widget class is the superclass of all widgets.
 * Widgets should be used in a WidgetList (defined in
 * widget_list.h), which will render and update them
 * properly.
 */
class Widget {
public:
    virtual void render(sf::RenderWindow*) {};
    virtual void update(float dt, bool down, float x, float y) {};
    virtual void handleEvent(sf::Event*) {};
    virtual float getHeight() { return 0; };
    virtual void setPosition(float x, float y) {};
};

/** TitleWidget : public Widget
 *
 * The TitleWidget displays some large text.
 */
class TitleWidget : public Widget {
    sf::Font *font;
    std::string string;
    sf::Text text;

public:
    TitleWidget() = default;
    TitleWidget(sf::Font*, std::string);
    void render(sf::RenderWindow*) override;
    float getHeight() override;
    void setPosition(float, float) override;
};

/** TextWidget : public Widget
 *
 * The TextWidget displays some regular text.
 */
class TextWidget : public Widget {
    sf::Font *font;
    std::string string;
    bool isHeader;
    sf::Text text;

public:
    TextWidget() = default;
    TextWidget(sf::Font*, std::string, bool);
    void render(sf::RenderWindow*) override;
    float getHeight() override;
    void setPosition(float, float) override;
    void setString(std::string str);
};

/** SpaceWidget : public Widget
 *
 * The SpaceWidget is just a vertical gap of 50px.
 */
class SpaceWidget : public Widget {
public:
    SpaceWidget() = default;
    void render(sf::RenderWindow*) override {};
    float getHeight() override { return 50; };
    void setPosition(float, float) override {};
};

/** ButtonWidget : public Widget
 *
 * The ButtonWidget renders a box with a label,
 * and when the box is clicked calls a function.
 */
class ButtonWidget : public Widget {
    sf::Font *font;
    std::string label;
    sf::Text text;
    sf::RectangleShape rect;

public:
    ButtonWidget() = default;
    ButtonWidget(sf::Font*, std::string);
    void render(sf::RenderWindow*) override;
    float getHeight() override;
    void setPosition(float, float) override;
    void handleEvent(sf::Event*) override;
    void update(float dt, bool down, float x, float y) override;

    std::function<void ()> callback;
};

/** SliderWidget : public Widget
 *
 * The SliderWidget allows the user to choose a
 * float value from min to max, inclusive.
 */
class SliderWidget : public Widget {
    sf::Font *font;
    sf::Text label, valPopover;
    sf::RectangleShape track, handle;
    float min, max;
    bool holding = false;

    float getProgress();
    void setProgress(float);
    void updateValPopover();

public:
    float value;

    SliderWidget() = default;
    SliderWidget(sf::Font*, std::string, float min, float max);
    void render(sf::RenderWindow*) override;
    float getHeight() override;
    void setPosition(float x, float y) override;
    void handleEvent(sf::Event*) override;
    void update(float dt, bool down, float x, float y) override;
};

#endif //SOLAR_SYSTEM_WIDGET_H
