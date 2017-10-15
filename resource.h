//
// Created by Zac G on 10/10/2017.
//

#ifndef SOLAR_SYSTEM_RESOURCE_H
#define SOLAR_SYSTEM_RESOURCE_H

#include <map>

/** ResourceType
 *
 * A type of resource, e.g. metal.
 */
enum ResourceType {
    Metal,
    Wood,
    Water,
    Population,
    Species,
    Food,
    Weaponary
};

typedef std::map<ResourceType, int> Store;

/** Resources
 *
 * Contains a Store (std::map<ResourceType, int>) and
 * some useful operators.
 */
class Resources {
public:
    Store store;

    Resources();
    Resources operator+(Resources);
    Resources operator-(Resources);

    // Checks if the given resources could be removed from this,
    // to still have >= 0 resources for each type.
    bool operator>(Resources);
};

#endif //SOLAR_SYSTEM_RESOURCE_H
