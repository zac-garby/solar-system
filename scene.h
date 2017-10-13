//
// Created by Zac G on 07/10/2017.
//

#ifndef SOLAR_SCENE_H
#define SOLAR_SCENE_H

#include <SFML/Graphics.hpp>

using namespace std;

class Scene {
public:
    virtual Scene *update(float) { return NULL; };
    virtual void render(sf::RenderWindow*) {};
    virtual Scene *handleEvent(sf::Event*) { return NULL; };
};


#endif //SOLAR_SCENE_H
