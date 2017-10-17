//
// Created by Zac G on 08/10/2017.
//

#include "sidebar.h"

std::string formatNumber(int n) {
    std::string s;
    int cnt = 0;

    do {
        s.insert(0, 1, char('0' + n % 10));
        n /= 10;

        if (++cnt == 3 && n) {
            s.insert(0, 1, ',');
            cnt = 0;
        }
    } while (n);

    return s;
}

/*********************/
/** PlanetInspector **/
/*********************/

PlanetInspector::PlanetInspector(Planet *planet)
    : timeLastUpdate(0.0f) {

    body.loadFromFile("assets/fonts/Cabin-Regular.ttf");
    header.loadFromFile("assets/fonts/Cabin-Bold.ttf");

    this->planet = planet;

    if (planet != nullptr) {

        // Initialise and add all the widgets

        title = TitleWidget(&header, planet->name);

        widgets.addWidget(&title);
        widgets.addWidget(&space);

        physical = TextWidget(&header, "Physical Properties", true);
        distance = TextWidget(&body, "Distance from sun: " + formatNumber(int(planet->distanceFromSun / 80)) + " AU", false);
        radius = TextWidget(&body, "Radius: " + formatNumber(int(planet->radius)) + " m", false);
        mass = TextWidget(&body, "Mass: " + formatNumber(int(planet->mass * 1E-24)) + " yg", false);
        speed = TextWidget(&body, "Speed: " + formatNumber(int(planet->speed)) + " miles/s", false);
        gravity = TextWidget(&body, "Gravity: " + formatNumber(int(planet->gravity)) + " g", false);

        widgets.addWidget(&physical);
        widgets.addWidget(&distance);
        widgets.addWidget(&radius);
        widgets.addWidget(&mass);
        widgets.addWidget(&speed);
        widgets.addWidget(&gravity);
        widgets.addWidget(&space);

        life = TextWidget(&header, "Life", true);
        population = TextWidget(&body, "Population: " + formatNumber(planet->resources.store[Population]) + " inhabitants", false);
        species = TextWidget(&body, "Species: " + formatNumber(planet->resources.store[Species]) + " species", false);
        inhabitants = TextWidget(&body, "Inhabitants: " + planet->getInhabitantName(), false);
        biodiversity = TextWidget(&body, "Biodiveristy: " + formatNumber(int(planet->biodiversity)), false);

        widgets.addWidget(&life);
        widgets.addWidget(&population);
        widgets.addWidget(&species);
        widgets.addWidget(&inhabitants);
        widgets.addWidget(&biodiversity);
        widgets.addWidget(&space);

        resources = TextWidget(&header, "Resources", true);
        metal = TextWidget(&body, "Metal: " + formatNumber(planet->resources.store[Metal]) + " tons", false);
        wood = TextWidget(&body, "Wood: " + formatNumber(planet->resources.store[Wood]) + " tons", false);
        water = TextWidget(&body, "Water: " + formatNumber(planet->resources.store[Water]) + " cubic feet", false);
        food = TextWidget(&body, "Food: " + formatNumber(planet->resources.store[Food]) + " units", false);
        weaponary = TextWidget(&body, "Weaponary: " + formatNumber(planet->resources.store[Weaponary]) + " units", false);

        widgets.addWidget(&resources);
        widgets.addWidget(&metal);
        widgets.addWidget(&wood);
        widgets.addWidget(&water);
        widgets.addWidget(&food);
        widgets.addWidget(&weaponary);
    }

    // Create noPlanet - an sf::Text which is displayed when
    // this sidebar is active, but no planet is selected.
    noPlanet.setFont(header);
    noPlanet.setString("No planet selected...");
    noPlanet.setCharacterSize(N(20));
    noPlanet.setFillColor(sf::Color(NO_PLANET_FG));
    sf::FloatRect bounds = noPlanet.getLocalBounds();
    noPlanet.setPosition(
            SIDEBAR_WIDTH / 2 - bounds.width / 2,
            HALF_HEIGHT - bounds.height / 2
    );

    // Create the background rectangle
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

void PlanetInspector::update(float dt) {
    if (nullptr == planet) {
        timeLastUpdate = 0.0f;
        return;
    }

    timeLastUpdate += dt;
    if (timeLastUpdate >= SIDEBAR_UPDATE_TIME_S) {
        timeLastUpdate -= SIDEBAR_UPDATE_TIME_S;
        updateWidgets();
    }
}

void PlanetInspector::updateWidgets() {
    if (nullptr == planet)
        return;
    
    distance.setString("Distance from sun: " + formatNumber(int(planet->distanceFromSun / 80)) + " AU");
    radius.setString("Radius: " + formatNumber(int(planet->radius)) + " m");
    mass.setString("Mass: " + formatNumber(int(planet->mass * 1E-24)) + " yg");
    speed.setString("Speed: " + formatNumber(int(planet->speed)) + " miles/s");
    gravity.setString("Gravity: " + formatNumber(float(planet->gravity)) + " g");

    population.setString("Population: " + formatNumber(planet->resources.store[Population]) + " inhabitants");
    species.setString("Species: " + formatNumber(planet->resources.store[Species]) + " species");
    inhabitants.setString("Inhabitants: " + planet->getInhabitantName());
    biodiversity.setString("Biodiveristy: " + formatNumber(int(planet->biodiversity)));

    metal.setString("Metal: " + formatNumber(planet->resources.store[Metal]) + " tons");
    wood.setString("Wood: " + formatNumber(planet->resources.store[Wood]) + " tons");
    water.setString("Water: " + formatNumber(planet->resources.store[Water]) + " cubic feet");
    populationResource.setString("Population: " + formatNumber(planet->resources.store[Population]) + " inhabitants");
    food.setString("Food: " + formatNumber(planet->resources.store[Food]) + " tons");
    weaponary.setString("Weaponary: " + formatNumber(planet->resources.store[Weaponary]) + " units");
}


/******************/
/** ShipDesigner **/
/******************/

ShipDesigner::ShipDesigner(Game *game, Planet *sender, Planet *destination): sender(sender), destination(destination) {
    // Load the required fonts
    body.loadFromFile("assets/fonts/Cabin-Regular.ttf");
    header.loadFromFile("assets/fonts/Cabin-Bold.ttf");

    // Create and add the widgets
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

    // When launch is clicked, launch a ship from the sender
    // containing the specified resources. Also, remove this sidebar,
    // defaulting back to the 'No planet selected' sidebar.
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

    // Create the background
    background = sf::RectangleShape(sf::Vector2f(SIDEBAR_WIDTH, HEIGHT));
    background.setFillColor(sf::Color(SIDEBAR_BG));
}

void ShipDesigner::render(sf::RenderWindow *win) {
    Sidebar::render(win);

    widgets.render(win);
}

void ShipDesigner::update(float dt) {
    widgets.update(dt);

    // Update the values of the sender resource indicators
    metal.setString("Metal: " + formatNumber(sender->resources.store[Metal]));
    population.setString("Population: " + formatNumber(sender->resources.store[Population]));
    food.setString("Food: " + formatNumber(sender->resources.store[Food]));
    weaponary.setString("Weaponary: " + formatNumber(sender->resources.store[Weaponary]));
}

void ShipDesigner::handleEvent(sf::Event *event) {
    widgets.handleEvent(event);
}
