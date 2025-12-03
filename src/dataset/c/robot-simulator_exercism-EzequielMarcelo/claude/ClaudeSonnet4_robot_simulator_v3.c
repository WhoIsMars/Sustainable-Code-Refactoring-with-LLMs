#include "robot_simulator.h"

static const int dx[] = {0, 1, 0, -1};
static const int dy[] = {1, 0, -1, 0};

robot_status_t robot_create(robot_direction_t direction, int x, int y) 
{
    return (robot_status_t){.direction = direction, .position = {x, y}};
}

void turn_left(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 3) & 3;
}

void turn_right(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 1) & 3;
}

void advance(robot_status_t *robot) 
{
    robot->position.x += dx[robot->direction];
    robot->position.y += dy[robot->direction];
}

void robot_move(robot_status_t *robot, const char *commands) 
{
    for (const char *cmd = commands; *cmd; cmd++) 
    {
        switch (*cmd) 
        {
            case 'R': robot->direction = (robot->direction + 1) & 3; break;
            case 'L': robot->direction = (robot->direction + 3) & 3; break;
            case 'A': 
                robot->position.x += dx[robot->direction];
                robot->position.y += dy[robot->direction];
                break;
        }
    }
}