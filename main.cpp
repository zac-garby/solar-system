#include <SFML/Graphics.hpp>

#include "config.h"
#include "scene.h"
#include "mainmenu.h"

// The current scene, e.g. main menu or game
Scene *scene;

// Used to calculate delta time
sf::Clock deltaClock;

int main() {
    // Seed random number generator based on system time
    srand(time(nullptr));

    // Enable antialasing at level 8
    // Maybe will be in settings later
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // A normal window, but non-resizable
    auto flags = sf::Style::Titlebar | sf::Style::Close;

    // Create the window, with a title "Solar System"
    // VSync is enabled, and key repeat is disabled
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Solar System", flags, settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    // Set the initial scene to the main menu
    scene = new MainMenu();

    // Main game loop
    while (window.isOpen()) {
        // Calculate delta time
        float dt = deltaClock.restart().asSeconds();

        sf::Event event;

        // For each event on the window
        while (window.pollEvent(event)) {

            // If it's a window close event, close the window
            // This will, of course, exit the loop
            if (event.type == sf::Event::Closed) window.close();

            // Pipe the event to the scene for further usage
            Scene *next = scene->handleEvent(&event);

            // If the scene returned a scene change, change to it
            if (next != nullptr) scene = next;
        }

        // Update the scene with the calculated delta time
        Scene *next = scene->update(dt);

        // If the scene returned a scene change, change to it
        if (next != nullptr) scene = next;

        // Clear the window and render the scene
        window.clear(sf::Color(CLEAR_COLOUR));
        scene->render(&window);
        window.display();
    }
}