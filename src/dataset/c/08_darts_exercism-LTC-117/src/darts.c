#include <math.h>

#include "darts.h"


uint8_t score(coordinate_t coordinates)
{
    uint8_t points = 0;

    float outer_radius = 10.0;
    float middle_radius = 5.0;
    float inner_radius = 1.0;

    // Applying the distance bewteen two points formula:
    // d² = (x1 - x0)² + (y1 - y0)²
    // Since 'x0' and 'y0' indicate the center coordinates, they're always 0.
    float pos = sqrt(pow(coordinates.x_axis, 2) + pow(coordinates.y_axis, 2));

    if (pos > outer_radius)
        points = 0;
    else if (pos <= outer_radius && pos > middle_radius)
        points = 1;
    else if (pos <= middle_radius && pos > inner_radius)
        points = 5;
    else
        points = 10;

    return points;
}
