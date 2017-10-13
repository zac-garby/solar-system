//
// Created by Zac G on 10/10/2017.
//

#ifndef SOLAR_SYSTEM_RESOURCE_H
#define SOLAR_SYSTEM_RESOURCE_H

#include <map>

enum ResourceType {
    Metal,
    Population,
    Food,
    Weaponary
};

typedef std::map<ResourceType, int> Store;

class Resources {
public:
    Store store;

    Resources();
    Resources operator+(Resources);
    Resources operator-(Resources);
    bool operator>(Resources);
};

#endif //SOLAR_SYSTEM_RESOURCE_H
