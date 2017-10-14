//
// Created by Zac G on 07/10/2017.
//

#ifndef SOLAR_SCENE_H
#define SOLAR_SCENE_H

#include <SFML/Graphics.hpp>

using namespace std;

/**
 * A very basic class which other scenes will extend.
 *
 * If update() or handleEvent() returns non-null, the game should
 * switch to the returned scene.
 */
class Scene {
public:
    virtual Scene *update(float) { return nullptr; };
    virtual void render(sf::RenderWindow*) {};
    virtual Scene *handleEvent(sf::Event*) { return nullptr; };
};


#endif //SOLAR_SCENE_H
