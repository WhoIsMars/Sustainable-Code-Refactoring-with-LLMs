#include "robot_simulator.h"
#include <stdio.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t newRobot = {direction, {x, y}};
    return newRobot;
}

void robot_move(robot_status_t *robot, const char *commands)
{
    for (const char *c = commands; *c != '\0'; ++c)
    {
        switch (*c)
        {
        case 'R':
            robot->direction = (robot->direction + 1) % 4;
            break;
        case 'L':
            robot->direction = (robot->direction + 3) % 4;
            break;
        default: 
        {
            switch (robot->direction)
            {
            case DIRECTION_NORTH:
                robot->position.y++;
                break;
            case DIRECTION_EAST:
                robot->position.x++;
                break;
            case DIRECTION_SOUTH:
                robot->position.y--;
                break;
            case DIRECTION_WEST:
                robot->position.x--;
                break;
            }
            break;
        }
        }
    }
}