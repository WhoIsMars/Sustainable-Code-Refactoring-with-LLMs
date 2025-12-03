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
    // Pre-compute direction deltas for advance command
    static const int dx[] = {0, 1, 0, -1}; // NORTH, EAST, SOUTH, WEST
    static const int dy[] = {1, 0, -1, 0}; // NORTH, EAST, SOUTH, WEST
    
    const char *cmd = commands;
    while (*cmd) {
        switch (*cmd) {
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
        ++cmd;
    }
}