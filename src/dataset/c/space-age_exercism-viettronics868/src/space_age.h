#ifndef SPACE_AGE_H
#define SPACE_AGE_H

#include <stdint.h>

typedef enum planet {
   MERCURY,
   VENUS,
   EARTH,
   MARS,
   JUPITER,
   SATURN,
   URANUS,
   NEPTUNE,
} planet_t;

float age(planet_t planet, uint64_t seconds);
float seconds_to_Earth_year(uint64_t seconds);
float planet_to_Earth_year(planet_t planet);

#endif
