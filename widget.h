//
// Created by Zac G on 11/10/2017.
//

#ifndef SOLAR_SYSTEM_WIDGET_H
#define SOLAR_SYSTEM_WIDGET_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "config.h"

class Widget {
public:
    virtual void render(sf::RenderWindow*) {};
    virtual void update(float dt, bool down, float x, float y) {};
    virtual void handleEvent(sf::Event*) {};
    virtual float getHeight() { return 0; };
    virtual void setPosition(float, float) {};
};

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

class SpaceWidget : public Widget {
public:
    SpaceWidget() = default;
    void render(sf::RenderWindow*) override {};
    float getHeight() override { return 50; };
    void setPosition(float, float) override {};
};

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
    void setMax(float newMax);
};

#endif //SOLAR_SYSTEM_WIDGET_H
