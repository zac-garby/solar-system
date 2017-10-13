//
// Created by Zac G on 08/10/2017.
//

#include "sidebar.h"

/*********************/
/** PlanetInspector **/
/*********************/

PlanetInspector::PlanetInspector(Planet *planet) {
    body.loadFromFile("assets/fonts/Cabin-Regular.ttf");
    header.loadFromFile("assets/fonts/Cabin-Bold.ttf");

    this->planet = planet;

    if (planet != nullptr) {
        title = TitleWidget(&header, planet->name);

        widgets.addWidget(&title);
        widgets.addWidget(&space);

        physical = TextWidget(&header, "Physical Properties", true);
        distance = TextWidget(&body, "Distance from sun: " + std::to_string(int(planet->distanceFromSun / 80)) + " AU", false);
        radius = TextWidget(&body, "Radius: " + std::to_string(int(planet->radius)) + " miles", false);
        mass = TextWidget(&body, "Mass: " + std::to_string(int(planet->mass)) + " yg", false);
        speed = TextWidget(&body, "Speed: " + std::to_string(int(planet->speed)) + " miles/s", false);

        widgets.addWidget(&physical);
        widgets.addWidget(&distance);
        widgets.addWidget(&radius);
        widgets.addWidget(&mass);
        widgets.addWidget(&speed);
        widgets.addWidget(&space);

        life = TextWidget(&header, "Life", true);
        population = TextWidget(&body, "Population: " + std::to_string(planet->resources.store[Population]), false);
        inhabitants = TextWidget(&body, "Inhabitants: " + planet->getInhabitantName(), false);

        widgets.addWidget(&life);
        widgets.addWidget(&population);
        widgets.addWidget(&inhabitants);
        widgets.addWidget(&space);

        resources = TextWidget(&header, "Resources", true);
        metal = TextWidget(&body, "Metal: " + std::to_string(planet->resources.store[Metal]), false);
        populationResource = TextWidget(&body, "Population: " + std::to_string(planet->resources.store[Population]), false);
        food = TextWidget(&body, "Food: " + std::to_string(planet->resources.store[Food]), false);
        weaponary = TextWidget(&body, "Weaponary: " + std::to_string(planet->resources.store[Weaponary]), false);

        widgets.addWidget(&resources);
        widgets.addWidget(&metal);
        widgets.addWidget(&populationResource);
        widgets.addWidget(&food);
        widgets.addWidget(&weaponary);
    }

    noPlanet.setFont(header);
    noPlanet.setString("No planet selected...");
    noPlanet.setCharacterSize(60);
    noPlanet.setFillColor(sf::Color(NO_PLANET_FG));
    sf::FloatRect bounds = noPlanet.getLocalBounds();
    noPlanet.setPosition(
            SIDEBAR_WIDTH / 2 - bounds.width / 2,
            HALF_HEIGHT - bounds.height / 2
    );

    background = sf::RectangleShape(sf::Vector2f(SIDEBAR_WIDTH, HEIGHT));
    background.setFillColor(sf::Color(SIDEBAR_BG));
}

void PlanetInspector::render(sf::RenderWindow *win) {
    Sidebar::render(win);

    if (planet == nullptr) {
        win->draw(noPlanet);
    } else {
        widgets.render(win);
    }
}



/******************/
/** ShipDesigner **/
/******************/

ShipDesigner::ShipDesigner(Game *game, Planet *sender, Planet *destination): sender(sender), destination(destination) {
    body.loadFromFile("assets/fonts/Cabin-Regular.ttf");
    header.loadFromFile("assets/fonts/Cabin-Bold.ttf");

    title = TitleWidget(&header, "Ship Designer");

    widgets.addWidget(&title);
    widgets.addWidget(&space);

    planetsText = TextWidget(&header, sender->name + " to " + destination->name, true);

    widgets.addWidget(&planetsText);
    widgets.addWidget(&space);

    resourcesHeader = TextWidget(&header, "Sender's Resources", true);
    metal = TextWidget(&body, "Metal:", false);
    population = TextWidget(&body, "Population:", false);
    food = TextWidget(&body, "Food:", false);
    weaponary = TextWidget(&body, "Weaponary:", false);

    widgets.addWidget(&resourcesHeader);
    widgets.addWidget(&metal);
    widgets.addWidget(&population);
    widgets.addWidget(&food);
    widgets.addWidget(&weaponary);
    widgets.addWidget(&space);

    metalSlider = SliderWidget(&body, "Metal", 0, min(MAX_CARGO_PER_RESOURCE, sender->resources.store[Metal] - SHIP_METAL_USAGE));
    populationSlider = SliderWidget(&body, "People", 0, min(MAX_CARGO_PER_RESOURCE, sender->resources.store[Population]));
    foodSlider = SliderWidget(&body, "Food", 0, min(MAX_CARGO_PER_RESOURCE, sender->resources.store[Food]));
    weaponarySlider = SliderWidget(&body, "Weaponary", 0, min(MAX_CARGO_PER_RESOURCE, sender->resources.store[Weaponary]));

    widgets.addWidget(&metalSlider);
    widgets.addWidget(&populationSlider);
    widgets.addWidget(&foodSlider);
    widgets.addWidget(&weaponarySlider);
    widgets.addWidget(&space);

    launch = ButtonWidget(&header, "Launch");
    launch.callback = [=] {
        Resources resources;
        resources.store = {
                {Metal, metalSlider.value},
                {Population, populationSlider.value},
                {Food, foodSlider.value},
                {Weaponary, weaponarySlider.value}
        };

        sender->resources.store[Metal] -= SHIP_METAL_USAGE;

        if (sender->resources > resources) sender->launchShip(resources, destination);

        // Change the sidebar to a 'No planet selected' one
        game->removeSidebar();
    };

    widgets.addWidget(&launch);

    background = sf::RectangleShape(sf::Vector2f(SIDEBAR_WIDTH, HEIGHT));
    background.setFillColor(sf::Color(SIDEBAR_BG));
}

void ShipDesigner::render(sf::RenderWindow *win) {
    Sidebar::render(win);

    widgets.render(win);
}

void ShipDesigner::update(float dt) {
    widgets.update(dt);

    metal.setString("Metal: " + std::to_string(sender->resources.store[Metal]));
    population.setString("Population: " + std::to_string(sender->resources.store[Population]));
    food.setString("Food: " + std::to_string(sender->resources.store[Food]));
    weaponary.setString("Weaponary: " + std::to_string(sender->resources.store[Weaponary]));
}

void ShipDesigner::handleEvent(sf::Event *event) {
    widgets.handleEvent(event);
}
