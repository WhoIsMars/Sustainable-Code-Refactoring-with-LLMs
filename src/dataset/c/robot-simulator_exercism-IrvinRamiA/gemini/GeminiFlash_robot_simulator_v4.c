#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t robot;

    robot.direction = direction;
    robot.position.x = x;
    robot.position.y = y;

    return robot;
}

void robot_move(robot_status_t *robot, const char *commands)
{
    const char *cmd = commands;
    while (*cmd)
    {
        switch (*cmd)
        {
        case 'R':
            robot->direction = (robot->direction == DIRECTION_WEST) ? DIRECTION_NORTH : (robot_direction_t)(robot->direction + 1);
            break;
        case 'L':
            robot->direction = (robot->direction == DIRECTION_NORTH) ? DIRECTION_WEST : (robot_direction_t)(robot->direction - 1);
            break;
        case 'A':
            switch (robot->direction)
            {
            case DIRECTION_NORTH:
                robot->position.y++;
                break;
            case DIRECTION_SOUTH:
                robot->position.y--;
                break;
            case DIRECTION_EAST:
                robot->position.x++;
                break;
            case DIRECTION_WEST:
                robot->position.x--;
                break;
            }
            break;
        default:
            break;
        }
        cmd++;
    }
}