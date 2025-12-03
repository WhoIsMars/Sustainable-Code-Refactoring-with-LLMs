#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t status = {.direction = direction,
                             .position = {.x = x,
                                          .y = y}};
    return status;
}

static inline void robot_advance(robot_status_t *robot)
{
    static const int dx[] = {0, 1, 0, -1};
    static const int dy[] = {1, 0, -1, 0};
    
    robot->position.x += dx[robot->direction];
    robot->position.y += dy[robot->direction];
}

void robot_move(robot_status_t *robot, const char *commands)
{
    const char *cmd = commands;
    
    while (*cmd) {
        switch (*cmd) {
        case 'R':
            robot->direction = (robot_direction_t)((robot->direction + 1) & 3);
            break;
        case 'L':
            robot->direction = (robot_direction_t)((robot->direction + 3) & 3);
            break;
        case 'A':
            robot_advance(robot);
            break;
        }
        cmd++;
    }
}