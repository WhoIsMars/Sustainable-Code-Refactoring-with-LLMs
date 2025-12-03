#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    return (robot_status_t){.direction = direction, .position = {.x = x, .y = y}};
}

static inline void robot_advance(robot_status_t *robot)
{
    static const int dx[] = {0, 0, 1, -1};
    static const int dy[] = {1, -1, 0, 0};
    robot->position.x += dx[robot->direction];
    robot->position.y += dy[robot->direction];
}

void robot_move(robot_status_t *robot, const char *commands)
{
    for (const char *cmd = commands; *cmd; ++cmd)
    {
        switch (*cmd)
        {
        case 'R':
            robot->direction = (robot_direction_t)((robot->direction + 1) % DIRECTION_MAX);
            break;
        case 'L':
            robot->direction = (robot_direction_t)((robot->direction + DIRECTION_MAX - 1) % DIRECTION_MAX);
            break;
        case 'A':
            robot_advance(robot);
            break;
        }
    }
}