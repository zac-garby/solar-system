//
// Created by Zac G on 14/10/2017.
//

#include "planet_relationships.h"

PlanetRelationships::PlanetRelationships() {
    relations = {};
}

PlanetRelationships::PlanetRelationships(std::vector<Planet*> planets) {
    for (int i = 0; i < planets.size(); i++) {
        Planet *a = planets[i];

        for (int j = i + 1; j < planets.size(); j++) {
            Planet *b = planets[j];

            std::pair<Planet*, Planet*> pair(a, b);
            relations[pair] = 0;
        }
    }
}

float PlanetRelationships::get(Planet *a, Planet *b) {
    std::pair<Planet*, Planet*> pair(a, b);

    return relations[pair];
}

void PlanetRelationships::set(Planet *a, Planet *b, float to) {
    std::pair<Planet*, Planet*> pair(a, b);

    if (to > MAX_PLANET_REL) to = MAX_PLANET_REL;
    if (to < MIN_PLANET_REL) to = MIN_PLANET_REL;

    relations[pair] = to;
}

void PlanetRelationships::shift(Planet *a, Planet *b, float delta) {
    float old = get(a, b);
    set(a, b, old + delta);
}
