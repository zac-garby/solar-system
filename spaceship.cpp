//
// Created by Zac G on 10/10/2017.
//

#include "spaceship.h"

unsigned int Spaceship::nextID = 0;

Spaceship::Spaceship(Planet *sender, Planet *destination, Resources resources):
        sender(sender),
        destination(destination),
        resources(resources) {

    // Take required resources from sender
    sender->resources = sender->resources - resources;

    // It hasn't delivered its resources yet
    delivered = false;

    // Assign a unique ID
    id = nextID++;

    // Create CircleShape to render
    shape = sf::CircleShape(SHIP_RADIUS, SHIP_SHAPE);
    shape.setFillColor(sf::Color(SHIP_COLOUR));
    shape.setOrigin(SHIP_RADIUS, SHIP_RADIUS);

    position = sender->getPosition(SYSTEM_CENTER);
    shape.setPosition(position);

    // Initial velocity = {0, 0}
    velocity.x = 0;
    velocity.y = 0;
}

void Spaceship::update(float dt) {
    // Calculate velocity to apply
    sf::Vector2f direction = getDirectionToDestination();
    direction.x *= SHIP_SPEED * dt + (1/(double)2) * SHIP_ACCELERATION * (dt)*(dt);
    direction.y *= SHIP_SPEED * dt + (1/(double)2) * SHIP_ACCELERATION * (dt)*(dt);

    // Apply new velocity, divide by drag
    velocity += direction;
    velocity.x *= SHIP_DRAG;
    velocity.y *= SHIP_DRAG;

    // Update position
    position += velocity;
    shape.setPosition(position);

    if (hasReachedDestination()) {
        delivered = true;

        // Move resources from sender to destination
        destination->resources = destination->resources + resources;
    }
}

void Spaceship::render(sf::RenderWindow *win) {
    win->draw(shape);
}

sf::Vector2f Spaceship::getDirectionToDestination() {
    sf::Vector2f dest = destination->getPosition(SYSTEM_CENTER);
    sf::Vector2f diff = dest - position;
    float length = sqrtf(diff.x * diff.x + diff.y * diff.y);

    return diff / length;
}

bool Spaceship::hasReachedDestination() {
    sf::Vector2f diff = destination->getPosition(SYSTEM_CENTER) - position;
    float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);

    return distance < destination->getPixelRadius();
}
