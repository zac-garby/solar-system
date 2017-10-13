//
// Created by Zac G on 08/10/2017.
//

#ifndef SOLAR_SYSTEM_MAINMENU_H
#define SOLAR_SYSTEM_MAINMENU_H

#include "config.h"
#include "scene.h"
#include "game.h"

class MainMenu : public Scene {
    sf::Font font, labelFont;
    sf::Text titleText, playLabel;
    sf::CircleShape playOrbit, playButton;

    void makeButton(sf::CircleShape*, sf::CircleShape*, sf::Text*, std::string, float, float, float);

public:
    MainMenu();

    Scene *update(float) override;
    void render(sf::RenderWindow*) override;
    Scene *handleEvent(sf::Event*) override;
};

#endif //SOLAR_SYSTEM_MAINMENU_H
