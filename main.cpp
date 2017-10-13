#include <SFML/Graphics.hpp>

#include "config.h"
#include "scene.h"
#include "mainmenu.h"

Scene *scene;
sf::Clock deltaClock;

int main() {
    srand(time(nullptr));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    auto flags = sf::Style::Titlebar | sf::Style::Close;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Solar System", flags, settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    scene = new MainMenu();

    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            Scene *next = scene->handleEvent(&event);
            if (next != nullptr) scene = next;
        }

        Scene *next = scene->update(dt);
        if (next != nullptr) scene = next;

        window.clear(sf::Color(CLEAR_COLOUR));
        scene->render(&window);
        window.display();
    }
}