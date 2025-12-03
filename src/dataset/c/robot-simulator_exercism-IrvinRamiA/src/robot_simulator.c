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
    while (*commands != '\0')
    {
        switch (*commands)
        {
        case 'R':
            if (robot->direction < DIRECTION_MAX - 1)
            {
                robot->direction++;
            }
            else
            {
                robot->direction = DIRECTION_DEFAULT;
            }
            break;
        case 'L':
            if (robot->direction > DIRECTION_DEFAULT)
            {
                robot->direction--;
            }
            else
            {
                robot->direction = DIRECTION_WEST;
            }
            break;
        case 'A':
            if (robot->direction == DIRECTION_NORTH)
            {
                robot->position.y++;
            }
            else if (robot->direction == DIRECTION_SOUTH)
            {
                robot->position.y--;
            }
            else if (robot->direction == DIRECTION_EAST)
            {
                robot->position.x++;
            }
            else if (robot->direction == DIRECTION_WEST)
            {
                robot->position.x--;
            }

            break;

        default:
            break;
        }

        commands++;
    }
}
