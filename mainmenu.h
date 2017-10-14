//
// Created by Zac G on 08/10/2017.
//

#ifndef SOLAR_SYSTEM_MAINMENU_H
#define SOLAR_SYSTEM_MAINMENU_H

#include "config.h"
#include "scene.h"
#include "game.h"

/** class MenuMenu : public Scene
 * The first scene a player will see. Shows
 * a title and a play button.
 */
class MainMenu : public Scene {
    sf::Font font, labelFont;
    sf::Text titleText, playLabel;
    sf::CircleShape playOrbit, playButton;

    // A helper to create a planet-like button at the given center and radius.
    void makeButton(sf::CircleShape*, sf::CircleShape*, sf::Text*, std::string, float, float, float);

public:
    MainMenu();

    Scene *update(float) override;
    void render(sf::RenderWindow*) override;
    Scene *handleEvent(sf::Event*) override;
};

#endif //SOLAR_SYSTEM_MAINMENU_H
