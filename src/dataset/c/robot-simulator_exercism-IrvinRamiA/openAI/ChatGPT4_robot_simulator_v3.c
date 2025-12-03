#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    return (robot_status_t){.direction = direction, .position = {.x = x, .y = y}};
}

void robot_move(robot_status_t *robot, const char *commands)
{
    static const int direction_offsets[4][2] = {
        {0, 1},  // DIRECTION_NORTH
        {1, 0},  // DIRECTION_EAST
        {0, -1}, // DIRECTION_SOUTH
        {-1, 0}  // DIRECTION_WEST
    };

    while (*commands)
    {
        switch (*commands++)
        {
        case 'R':
            robot->direction = (robot->direction + 1) % DIRECTION_MAX;
            break;
        case 'L':
            robot->direction = (robot->direction + DIRECTION_MAX - 1) % DIRECTION_MAX;
            break;
        case 'A':
            robot->position.x += direction_offsets[robot->direction][0];
            robot->position.y += direction_offsets[robot->direction][1];
            break;
        }
    }
}