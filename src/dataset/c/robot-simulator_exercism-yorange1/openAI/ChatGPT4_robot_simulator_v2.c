#include "robot_simulator.h"

#include <string.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    return (robot_status_t){.direction = direction, .position = {.x = x, .y = y}};
}

static inline void robot_advance(robot_status_t *robot)
{
    if (robot->direction == DIRECTION_NORTH)
        robot->position.y++;
    else if (robot->direction == DIRECTION_SOUTH)
        robot->position.y--;
    else if (robot->direction == DIRECTION_EAST)
        robot->position.x++;
    else if (robot->direction == DIRECTION_WEST)
        robot->position.x--;
}

void robot_move(robot_status_t *robot, const char *commands)
{
    for (const char *cmd = commands; *cmd != '\0'; ++cmd)
    {
        if (*cmd == 'R')
            robot->direction = (robot_direction_t)((robot->direction + 1) % DIRECTION_MAX);
        else if (*cmd == 'L')
            robot->direction = (robot_direction_t)((robot->direction + 3) % DIRECTION_MAX);
        else if (*cmd == 'A')
            robot_advance(robot);
    }
}