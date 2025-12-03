#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    return (robot_status_t){
        .direction = direction,
        .position = {.x = x, .y = y}
    };
}

void robot_move(robot_status_t *robot, const char *commands)
{
    static const int dx[] = {0, 1, 0, -1};
    static const int dy[] = {1, 0, -1, 0};
    
    for (const char *cmd = commands; *cmd; ++cmd)
    {
        switch (*cmd)
        {
        case 'R':
            robot->direction = (robot->direction + 1) & 3;
            break;
        case 'L':
            robot->direction = (robot->direction + 3) & 3;
            break;
        case 'A':
            robot->position.x += dx[robot->direction];
            robot->position.y += dy[robot->direction];
            break;
        }
    }
}