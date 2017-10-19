//
// Created by Zac G on 08/10/2017.
//

#ifndef SOLAR_SYSTEM_CONFIG_H
#define SOLAR_SYSTEM_CONFIG_H


/** Meta **/

#define ASSUMED_WIDTH 1920.f
#define WIDTH_RATIO (sf::VideoMode::getDesktopMode().width / ASSUMED_WIDTH)
#define N(n) ((n) * WIDTH_RATIO)

// The dimensions of the window
#define WIDTH N(1000)
#define HEIGHT N(700)
#define HALF_WIDTH (WIDTH / 2)
#define HALF_HEIGHT (HEIGHT / 2)

// The size of the sidebar
#define SIDEBAR_WIDTH (WIDTH - HEIGHT)

// Positioning of the solar system
#define SYSTEM_X (HALF_WIDTH + (SIDEBAR_WIDTH / 2))
#define SYSTEM_Y HALF_HEIGHT
#define SYSTEM_CENTER sf::Vector2f(SYSTEM_X, SYSTEM_Y)

// Font sizes
#define REGULAR_FONT_SIZE N(16)
#define TITLE_FONT_SIZE N(REGULAR_FONT_SIZE * 2 / 3)

// Widget dimensions
#define WIDGET_MARGIN N(15)
#define WIDGET_PADDING N(4)

#define BUTTON_HEIGHT N(25)

#define SLIDER_TRACK_HEIGHT N(5)
#define SLIDER_HANDLE_HEIGHT N(20)
#define SLIDER_HANDLE_WIDTH N(8)
#define SLIDER_LABEL_GAP N(10)

// The width of the line created when
// dragging one line to another
#define DRAG_LINE_WIDTH N(2)

// 1 game year = TIMESCALE real minutes
#define TIMESCALE 2

// Time (in seconds) between sidebar updates
#define SIDEBAR_UPDATE_TIME_S 1.0f

/** Constants **/
#define PI            3.14159f
#define AU_TO_METER   1.496E+11f
#define GRAVITY_CONST 6.67E-14f    // m^3 / g / s^2

// Earth constants
#define EARTH_RADIUS  6.371E+6f    // m
#define EARTH_MASS    5.972E+24f   // g
#define EARTH_DENSITY 5.51E+6f     // g / m^3
#define EARTH_G       9.8f         // m / s^2


/** Colours **/
#define CLEAR_COLOUR         20,  20,  20
#define SIDEBAR_BG           15,  15,  15
#define NO_PLANET_FG         70,  70,  70
#define ORBIT_COLOUR         50,  50,  50
#define LIGHT_FG            160, 160, 160
#define REGULAR_FG          120, 120, 120
#define BRIGHT_FG           210, 210, 210
#define BUTTON_BG            40,  40,  40
#define BUTTON_HOVER         90,  90,  90
#define BUTTON_ACTIVE        70,  70,  70
#define SLIDER_TRACK_BG      30,  30,  30
#define DRAG_LINE_COLOUR    200, 200, 200, 100


/** Planets **/

// The bounds of possible population.
// Note: population also has a chance to be 0
#define MIN_POPULATION 1000
#define MAX_POPULATION 5000000

// Bounds of possible density.
// Should probably be tweaked.
// Currently on minimum radius and minimum density capacity is 50k
// On maximum radius and maximum density capacity is 9million.
#define MIN_DENSITY 1E-5f
#define MAX_DENSITY 5E-4f

// Factor to convert planet radius from meters to screen pixels
#define RADIUS_TO_PIXEL_FACTOR 4E-3f

// The bounds of the planet likeness to Earth
#define MIN_EARTH_LIKENESS 0.5f
#define MAX_EARTH_LIKENESS 2.0f

// The extra pixels added to the planet radius to calculate its border
#define PLANET_BORDER_EXTRA_PIXELS N(2)
#define PLANET_BORDER_THICKNESS N(2)

// The bounds of planet speed
#define MIN_PLANET_SPEED 25
#define MAX_PLANET_SPEED 40

// The radius (in pixels) of the sun
#define SUN_RADIUS 60

// The number of planets to generate
#define NUM_PLANETS 5

// The minimum and maximum number of inhabited planets
#define MIN_REQ_INHABITED 2
#define MAX_REQ_INHABITED 4

// The minimum and maximum relation bounds
#define MIN_PLANET_REL (-1.f)
#define MAX_PLANET_REL (+1.f)


/** Spaceships **/

#define SHIP_RADIUS N(2)
#define SHIP_SHAPE 6
#define SHIP_COLOUR 220, 220, 220
#define SHIP_SPEED N(15)
#define SHIP_DRAG N(0.25)

// Ships can only carry this many of each resource
#define MAX_CARGO_PER_RESOURCE 5000L

// Each ship consumes this much metal from the sender
#define SHIP_METAL_USAGE 500

#endif //SOLAR_SYSTEM_CONFIG_H
