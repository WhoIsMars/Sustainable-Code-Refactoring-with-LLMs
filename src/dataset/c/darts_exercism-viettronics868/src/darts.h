#ifndef DARTS_H
#define DARTS_H

    #include <stdint.h>

    typedef struct {
        float x;
        float y;
    }coordinate_t;

    typedef enum {
        OUTER_CIRCLE,
        MIDDLE_CIRCLE,
        INNER_CIRCLE
    }target;

    uint8_t score(coordinate_t landing_position);

#endif
