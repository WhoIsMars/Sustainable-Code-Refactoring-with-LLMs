#include "robot_simulator.h"
#include <stdio.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t newRobot = {direction,{x,y}};
    return newRobot;
}

void robot_move(robot_status_t *robot, const char *commands)
{
    for (const char *c = commands; *c != '\0'; c++)
    {
        char action = *c;
        switch (action)
        {
        case 'R':
            robot->direction += 1;
            if(robot->direction > 3) robot->direction = 0;
            break;
        case 'L':
            if(robot->direction == 0)
            {
                robot->direction = 3;
                break;
            }
            robot->direction -= 1;
            break;
            // default is Advance
        default:
            switch (robot->direction)
            {
            case DIRECTION_NORTH:
                robot->position.y +=1;
                break;
            case DIRECTION_EAST:
                robot->position.x +=1;
                break;
            case DIRECTION_SOUTH:
                robot->position.y -=1;
                break;
            default:
                robot->position.x -=1;
                break;
            };
        }
    }
}
