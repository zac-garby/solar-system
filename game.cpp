//
// Created by Zac G on 08/10/2017.
//

#include "config.h"
#include "game.h"

Game::Game() {
    font.loadFromFile("assets/fonts/Cabin-Bold.ttf");
    yearDisplay = sf::Text("", font, REGULAR_FONT_SIZE);
    yearDisplay.setFillColor(sf::Color(BRIGHT_FG));

    sidebar = new PlanetInspector(nullptr);

    sun = sf::CircleShape(SUN_RADIUS, 50);
    sun.setPosition(SYSTEM_X, SYSTEM_Y);
    sun.setFillColor(sf::Color::Yellow);
    sun.setOrigin(SUN_RADIUS, SUN_RADIUS);

    int numberInhabited = 0;

    // Continuously generate new sets of planets until enough are inhabited.
    while (numberInhabited < MIN_REQ_INHABITED || numberInhabited > MAX_REQ_INHABITED) {
        planets.clear();

        float dist = SUN_RADIUS + N(50);

        for (int i = 0; i < NUM_PLANETS; i++) {
            Planet planet(dist);
            planets.push_back(planet);

            dist += planet.getPixelRadius() * 2 + N(20);
        }

        numberInhabited = 0;

        for (auto &planet : planets) {
            if (planet.resources.store[Population] > 0) numberInhabited++;
        }
    }

    std::vector<Planet*> pptrs;
    for (auto &planet : planets) pptrs.push_back(&planet);

    relationships = new PlanetRelationships(pptrs);

    dragLine = sf::RectangleShape(sf::Vector2f(DRAG_LINE_WIDTH, DRAG_LINE_WIDTH));
    dragLine.setOrigin(DRAG_LINE_WIDTH / 2, DRAG_LINE_WIDTH / 2);
    dragLine.setFillColor(sf::Color(DRAG_LINE_COLOUR));
}

Scene *Game::update(float dt) {
    elapsed += dt * 1000;

    for (auto &planet : planets) {
        planet.update(this, dt);
    }

    for (auto &ship : ships) {
        ship.update(dt);

        if (ship.delivered) {
            // Remove the ship if it's got to its destination

            int index = -1;

            for (int i = 0; i < ships.size(); i++) {
                if (ships[i].id == ship.id) {
                    index = i;
                    break;
                }
            }

            if (index >= 0) {
                ships.erase(ships.begin() + index);
            }

            // Update the sidebar
            if (auto pi = dynamic_cast<PlanetInspector*>(sidebar)) {
                sidebar = new PlanetInspector(pi->planet);
            }
        }
    }

    int date, month, year;
    std::tie(date, month, year) = getDate();

    yearDisplay.setString(std::to_string(date) + "/" + std::to_string(month) + "/" + std::to_string(year));

    sidebar->update(dt);

    getDate();

    return nullptr;
}

void Game::render(sf::RenderWindow *win) {
    positionDragLine(win);

    win->draw(sun);

    for (auto &planet : planets) {
        planet.renderOrbit(win);
    }

    renderRelationships(win);

    if (dragging) win->draw(dragLine);

    for (auto &ship : ships) {
        ship.render(win);
    }

    for (auto &planet : planets) {
        planet.render(win);
    }

    sf::FloatRect ydBounds = yearDisplay.getGlobalBounds();
    yearDisplay.setPosition(WIDTH - ydBounds.width - N(10), N(10));
    win->draw(yearDisplay);

    sidebar->render(win);
}

Scene *Game::handleEvent(sf::Event *event) {
    sf::Vector2f pos;

    switch (event->type) {
        case sf::Event::KeyReleased:
            switch (event->key.code) {
                case sf::Keyboard::Escape:
                    return new MainMenu();
                default:
                    return nullptr;
            }

        case sf::Event::MouseButtonPressed:
            pos = sf::Vector2f(event->mouseButton.x, event->mouseButton.y);

            switch (event->mouseButton.button) {
                case sf::Mouse::Left:
                    mouseDown(pos);

                default:
                    break;
            }

            break;

        case sf::Event::MouseButtonReleased:
            pos = sf::Vector2f(event->mouseButton.x, event->mouseButton.y);

            switch (event->mouseButton.button) {
                case sf::Mouse::Left:
                    mouseUp(pos);

                default:
                    break;
            }

            break;

        default:
            break;
    }

    sidebar->handleEvent(event);

    return nullptr;
}

void Game::mouseDown(sf::Vector2f pos) {
    dragging = false;

    if (pos.x > SIDEBAR_WIDTH) {
        selectPlanet(nullptr);

        bool found = false;
        for (auto &planet : planets) {
            if (planet.contains(pos)) {
                selectPlanet(&planet);
                found = true;

                break;
            }
        }

        if (found) dragging = true;
    }
}

void Game::mouseUp(sf::Vector2f pos) {
    dragging = false;

    if (selected == nullptr) return;

    for (auto &planet : planets) {

        // If the planet is moused over, isn't selected and is populated.
        if (planet.contains(pos) &&
                selected != &planet &&
                selected->resources.store[Population] > 0) {
            sidebar = new ShipDesigner(this, selected, &planet);

            break;
        }
    }
}

void Game::selectPlanet(Planet *planet) {
    sidebar = new PlanetInspector(planet);
    selected = planet;
}

void Game::removeSidebar() {
    sidebar = new PlanetInspector(nullptr);
}

void Game::positionDragLine(sf::Window *win) {
    if (selected == nullptr) return;

    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*win));
    sf::Vector2f selPos = selected->getPosition(SYSTEM_CENTER);
    sf::Vector2f diff = mouse - selPos;

    float length = sqrtf(diff.x * diff.x + diff.y * diff.y);
    float angle = atan2f(diff.x, diff.y);

    dragLine.setPosition(selPos);
    dragLine.setSize(sf::Vector2f(length, DRAG_LINE_WIDTH));
    dragLine.setRotation(-angle * (180 / PI) + 90);
}

void Game::renderRelationships(sf::RenderWindow *win) {
    std::vector<std::tuple<Planet*, Planet*, float>> edges;

    if (selected != nullptr) {
        for (auto &edge : relationships->relations) {
            if (edge.first.first == selected || edge.first.second == selected)
                edges.push_back({edge.first.first, edge.first.second, edge.second});
        }
    } else {
        for (auto &edge : relationships->relations) edges.push_back({edge.first.first, edge.first.second, edge.second});
    }

    for (auto &edge : edges) {
        float relationship;
        Planet *a, *b;

        std::tie(a, b, relationship) = edge;

        sf::Vector2f diff = b->getPosition(SYSTEM_CENTER) - a->getPosition(SYSTEM_CENTER);
        float length = sqrtf(diff.x * diff.x + diff.y * diff.y);
        float angle = atan2f(diff.x, diff.y);

        float r = 128 * -relationship + 127;
        float g = 256 - r;
        float alpha = abs(relationship) * 80;

        sf::RectangleShape rect(sf::Vector2f(length, N(1.5f)));
        rect.setFillColor(sf::Color(sf::Uint8(r), sf::Uint8(g), 0, sf::Uint8(alpha)));
        rect.setPosition(a->getPosition(SYSTEM_CENTER));
        rect.setRotation(-angle * (180 / PI) + 90);
        win->draw(rect);
    }
}

std::tuple<int, int, int> Game::getDate() {
    int millisPerDay = (TIMESCALE * 60 * 1000) / 365;
    int day = elapsed / millisPerDay;

    int months[] = {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    int date = 0, month = 0, year = 0, daysLeft = months[month];

    for (int i = 0; i < day; i++) {
        if (daysLeft == 0) {
            month++;
            date = 0;

            if (month >= 12) {
                month = 0;
                year++;
            }

            daysLeft = months[month];
        }

        date++;
        daysLeft--;
    }

    return {date, month + 1, year};
}