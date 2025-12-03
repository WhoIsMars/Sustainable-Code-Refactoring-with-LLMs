#include "robot_simulator.h"

void turn_left(robot_status_t *robot);
void turn_right(robot_status_t *robot);
void advance(robot_status_t *robot);

robot_status_t robot_create(robot_direction_t direction, int x, int y) 
{
    robot_status_t robot;
    robot.direction = direction;
    robot.position.x = x;
    robot.position.y = y;
    return robot;
}
void turn_left(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 3) % 4;
}

void turn_right(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 1) % 4;
}

void advance(robot_status_t *robot) 
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
        default:
            break;
    }
}

void robot_move(robot_status_t *robot, const char *commands) 
{
    for (const char *command = commands; *command != '\0'; command++) 
    {
        switch (*command) 
        {
            case 'R':
                turn_right(robot);
                break;
            case 'L':
                turn_left(robot);
                break;
            case 'A':
                advance(robot);
                break;
            default:
                break;
        }
    }
}