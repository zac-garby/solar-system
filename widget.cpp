//
// Created by Zac G on 11/10/2017.
//

#include <utility>
#include "widget.h"

TextWidget::TextWidget(sf::Font *font, std::string string, bool isHeader): font(font), string(string), isHeader(isHeader) {
    text = sf::Text(string, *font, REGULAR_FONT_SIZE);
    text.setFillColor(isHeader ? sf::Color(LIGHT_FG) : sf::Color(REGULAR_FG));

    if (isHeader) text.setStyle(sf::Text::Bold);
}

void TextWidget::render(sf::RenderWindow *win) {
    win->draw(text);
}

float TextWidget::getHeight() {
    return REGULAR_FONT_SIZE + N(3.5f);
}

void TextWidget::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void TextWidget::setString(std::string str) {
    text.setString(str);
}


TitleWidget::TitleWidget(sf::Font *font, std::string string): font(font), string(string) {
    text = sf::Text(string, *font, TITLE_FONT_SIZE);
    text.setFillColor(sf::Color(BRIGHT_FG));
    text.setStyle(sf::Text::Bold);
}

void TitleWidget::render(sf::RenderWindow *win) {
    win->draw(text);
}

float TitleWidget::getHeight() {
    return TITLE_FONT_SIZE + N(3.5f);
}

void TitleWidget::setPosition(float x, float y) {
    text.setPosition(x, y);
}


ButtonWidget::ButtonWidget(sf::Font *font, std::string label): font(font), label(label) {
    text = sf::Text(label, *font, REGULAR_FONT_SIZE);
    text.setFillColor(sf::Color(LIGHT_FG));

    rect.setSize(sf::Vector2f(SIDEBAR_WIDTH - WIDGET_MARGIN * 2, BUTTON_HEIGHT));
    rect.setFillColor(sf::Color(BUTTON_BG));

    callback = [] {};
}

void ButtonWidget::render(sf::RenderWindow *win) {
    win->draw(rect);
    win->draw(text);
}

float ButtonWidget::getHeight() {
    return BUTTON_HEIGHT;
}

void ButtonWidget::setPosition(float x, float y) {
    rect.setPosition(x, y);

    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect rectBounds = rect.getLocalBounds();
    text.setPosition(x + rectBounds.width / 2 - textBounds.width / 2, y + textBounds.height / 2);
}

void ButtonWidget::handleEvent(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonReleased) {
        sf::FloatRect bounds = rect.getGlobalBounds();

        if (bounds.contains(event->mouseButton.x, event->mouseButton.y)) {
            callback();
        }
    }
}

void ButtonWidget::update(float, bool down, float x, float y) {
    sf::FloatRect bounds = rect.getGlobalBounds();

    if (bounds.contains(x, y)) {
        rect.setFillColor(!down ? sf::Color(BUTTON_HOVER) : sf::Color(BUTTON_ACTIVE));
    } else {
        rect.setFillColor(sf::Color(BUTTON_BG));
    }
}


SliderWidget::SliderWidget(sf::Font *font, std::string string, float min, float max): font(font), min(min), max(max), value(0) {
    track.setSize(sf::Vector2f(SIDEBAR_WIDTH - WIDGET_MARGIN * 2, SLIDER_TRACK_HEIGHT));
    track.setFillColor(sf::Color(SLIDER_TRACK_BG));

    handle.setSize(sf::Vector2f(SLIDER_HANDLE_WIDTH, SLIDER_HANDLE_HEIGHT));
    handle.setFillColor(sf::Color(BUTTON_BG));
    handle.setOrigin(SLIDER_HANDLE_WIDTH / 2, SLIDER_HANDLE_HEIGHT / 2);

    label = sf::Text(string, *font, REGULAR_FONT_SIZE);
    label.setFillColor(sf::Color(LIGHT_FG));

    valPopover = sf::Text(std::to_string(lround(value)), *font, REGULAR_FONT_SIZE);
    valPopover.setFillColor(sf::Color(LIGHT_FG));
    valPopover.setStyle(sf::Text::Bold);

    sf::FloatRect labelBounds = label.getLocalBounds();
    track.setSize(sf::Vector2f(SIDEBAR_WIDTH - WIDGET_MARGIN * 2 - labelBounds.width - SLIDER_LABEL_GAP, SLIDER_TRACK_HEIGHT));

    updateValPopover();
}

void SliderWidget::render(sf::RenderWindow *win) {
    win->draw(track);
    win->draw(handle);
    win->draw(label);
    win->draw(valPopover);
}

float SliderWidget::getHeight() {
    return SLIDER_HANDLE_HEIGHT + 20;
}

void SliderWidget::setPosition(float x, float y) {
    sf::FloatRect labelBounds = label.getLocalBounds();
    label.setPosition(x, y + labelBounds.height / 2);

    track.setPosition(x + labelBounds.width + SLIDER_LABEL_GAP, y + SLIDER_HANDLE_HEIGHT / 2);

    sf::FloatRect trackBounds = track.getGlobalBounds();
    valPopover.setPosition(trackBounds.left + trackBounds.width / 2, trackBounds.top);
}

void SliderWidget::handleEvent(sf::Event *event) {
    sf::FloatRect handleBounds;

    switch (event->type) {
        case sf::Event::MouseButtonPressed:
            handleBounds = handle.getGlobalBounds();

            if (handleBounds.contains(event->mouseButton.x, event->mouseButton.y)) {
                holding = true;
            }

            break;

        case sf::Event::MouseButtonReleased:
            holding = false;

            break;

        default:
            break;
    }
}

void SliderWidget::update(float, bool down, float x, float y) {
    float progress = getProgress();

    sf::FloatRect trackBounds = track.getGlobalBounds();
    handle.setPosition(
            trackBounds.left + trackBounds.width * progress,
            trackBounds.top + SLIDER_TRACK_HEIGHT / 2
    );

    sf::FloatRect handleBounds = handle.getGlobalBounds();

    if (handleBounds.contains(x, y) || holding) {
        handle.setFillColor(!down ? sf::Color(BUTTON_HOVER) : sf::Color(BUTTON_ACTIVE));
    } else {
        handle.setFillColor(sf::Color(BUTTON_BG));
    }

    if (holding) {
        float mouseDistance = x - trackBounds.left;
        progress = mouseDistance / trackBounds.width;
        setProgress(progress);

        updateValPopover();
    }
}

float SliderWidget::getProgress() {
    return (value - min) / (max - min);
}

void SliderWidget::setProgress(float prog) {
    value = (max - min) * prog + min;

    if (value < min) value = min;
    if (value > max) value = max;
}

void SliderWidget::updateValPopover() {
    valPopover.setString(std::to_string(lround(value)));
    sf::FloatRect valBounds = valPopover.getLocalBounds();
    valPopover.setOrigin(valBounds.width / 2, valBounds.height / 2);
}

