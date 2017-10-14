//
// Created by Zac G on 08/10/2017.
//

#ifndef SOLAR_SYSTEM_CONFIG_H
#define SOLAR_SYSTEM_CONFIG_H

/** Meta **/

// The dimensions of the window
#define WIDTH 2200
#define HEIGHT 1500
#define HALF_WIDTH (WIDTH / 2)
#define HALF_HEIGHT (HEIGHT / 2)

// The size of the sidebar
#define SIDEBAR_WIDTH (WIDTH - HEIGHT)

// Positioning of the solar system
#define SYSTEM_X (HALF_WIDTH + (SIDEBAR_WIDTH / 2))
#define SYSTEM_Y HALF_HEIGHT
#define SYSTEM_CENTER sf::Vector2f(SYSTEM_X, SYSTEM_Y)

// Font sizes
#define REGULAR_FONT_SIZE 38
#define TITLE_FONT_SIZE (REGULAR_FONT_SIZE * 2)

// Widget dimensions
#define WIDGET_MARGIN 50
#define WIDGET_PADDING 10

#define BUTTON_HEIGHT 80

#define SLIDER_TRACK_HEIGHT 15
#define SLIDER_HANDLE_HEIGHT 60
#define SLIDER_HANDLE_WIDTH 25
#define SLIDER_LABEL_GAP 30

// The width of the line created when
// dragging one line to another
#define DRAG_LINE_WIDTH 5

/** Constants **/
#define PI 3.14159f

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

// The bounds of planet radii
#define MIN_RADIUS 20000
#define MAX_RADIUS 38000

// The bounds of planet speed
#define MIN_PLANET_SPEED 50
#define MAX_PLANET_SPEED 80

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

#define SHIP_RADIUS 3
#define SHIP_SHAPE 6
#define SHIP_COLOUR 220, 220, 220
#define SHIP_SPEED 30
#define SHIP_DRAG 0.8

// Ships can only carry this many of each resource
#define MAX_CARGO_PER_RESOURCE 5000

// Each ship consumes this much metal from the sender
#define SHIP_METAL_USAGE 500

#endif //SOLAR_SYSTEM_CONFIG_H
