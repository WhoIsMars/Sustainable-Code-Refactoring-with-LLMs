#include "robot_simulator.h"
#include <stdio.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t newRobot = {direction, {x, y}};
    return newRobot;
}

void robot_move(robot_status_t *robot, const char *commands)
{
    const char *c = commands;
    char action;
    
    while ((action = *c++) != '\0')
    {
        if (action == 'R')
        {
            robot->direction = (robot->direction + 1) & 3;
        }
        else if (action == 'L')
        {
            robot->direction = (robot->direction + 3) & 3;
        }
        else
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
            default:
                robot->position.x--;
                break;
            }
        }
    }
}