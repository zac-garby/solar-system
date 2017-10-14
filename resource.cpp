//
// Created by Zac G on 10/10/2017.
//

#include "resource.h"

Resources::Resources() {
    // Initialise all possible store fields
    store = {
            {Metal, 0},
            {Population, 0},
            {Food, 0},
            {Weaponary, 0}
    };
}

// Returns the sum of two resources
Resources Resources::operator+(Resources other) {
    Resources cp;

    for (auto &iter : store) {
        cp.store[iter.first] = iter.second + other.store[iter.first];
    }

    return cp;
}

// Returns the left resource minus the right, i.e. for every resource
// type, result[t] = left[t] - right[t]
Resources Resources::operator-(Resources other) {
    Resources cp;

    for (auto &iter : store) {
        cp.store[iter.first] = iter.second - other.store[iter.first];
    }

    return cp;
}

bool Resources::operator>(Resources other) {
    for (auto &iter : store) {
        int otherVal = other.store[iter.first];

        if (otherVal > iter.second) return false;
    }

    return true;
}
