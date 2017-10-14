//
// Created by Zac G on 08/10/2017.
//

#include "mainmenu.h"

MainMenu::MainMenu() {
    // Load the required fonts
    font.loadFromFile("assets/fonts/EspressoDolce.ttf");
    labelFont.loadFromFile("assets/fonts/Cabin-Bold.ttf");

    // Setup the main title, positioned in the center horizontally and
    // slightly down from the top.
    titleText.setFont(font);
    titleText.setString("Solar System");
    titleText.setCharacterSize(150);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = titleText.getLocalBounds();
    titleText.setPosition(HALF_WIDTH - bounds.width / 2, HEIGHT * 0.1f - bounds.height / 2);

    // Initialise the play button, with its orbit.
    makeButton(&playButton, &playOrbit, &playLabel, "Play", HEIGHT, N(45), -PI / 2);
}

Scene *MainMenu::update(float) {
    return nullptr;
}

void MainMenu::render(sf::RenderWindow *win) {
    // Render the title
    win->draw(titleText);

    // Render the play button
    win->draw(playOrbit);
    win->draw(playButton);
    win->draw(playLabel);
}

Scene *MainMenu::handleEvent(sf::Event *event) {
    if (event->type == sf::Event::MouseButtonReleased) {

        // Calculate pos and distance to play button to see if it was
        // clicked. This will have to be modified when more buttons are
        // added.
        sf::Vector2f pos(event->mouseButton.x, event->mouseButton.y);
        sf::Vector2f diff = playButton.getPosition() - pos;

        float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);

        // If the play button is clicked, go to the Game scene
        if (distance <= 130) return new Game();
    }

    return nullptr;
}

// Makes a main menu button in the style of a planet with an orbit.
void MainMenu::makeButton(
        sf::CircleShape *planet, sf::CircleShape *orbit, sf::Text *text,
        std::string label, float distance, float radius, float angle) {

    // The center of the orbit (below the bottom of the screen)
    sf::Vector2f center(HALF_WIDTH, HEIGHT * 1.6f);

    // The position of the planet relative to the center of orbit
    sf::Vector2f ppos(
            cosf(angle) * distance,
            sinf(angle) * distance
    );

    orbit->setPointCount(100);
    orbit->setRadius(distance);
    orbit->setOrigin(distance, distance);
    orbit->setPosition(center);
    orbit->setFillColor(sf::Color::Transparent);
    orbit->setOutlineThickness(6);
    orbit->setOutlineColor(sf::Color(ORBIT_COLOUR));

    planet->setPointCount(70);
    planet->setRadius(radius);
    planet->setOrigin(radius, radius);
    planet->setPosition(orbit->getPosition() + ppos);
    planet->setFillColor(sf::Color(BRIGHT_FG));

    text->setFont(labelFont);
    text->setString(label);
    text->setCharacterSize(radius / 2);
    sf::FloatRect textBounds = text->getLocalBounds();
    text->setOrigin(textBounds.width / 2, textBounds.height / 2 + N(3));
    text->setPosition(orbit->getPosition() + ppos);
    text->setFillColor(sf::Color(CLEAR_COLOUR));
}
