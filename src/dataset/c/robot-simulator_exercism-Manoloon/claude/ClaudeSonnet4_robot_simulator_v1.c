#include "robot_simulator.h"
#include <stdio.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t newRobot = {direction, {x, y}};
    return newRobot;
}

void robot_move(robot_status_t *robot, const char *commands)
{
    // Pre-compute direction deltas for movement
    static const int dx[] = {0, 1, 0, -1}; // NORTH, EAST, SOUTH, WEST
    static const int dy[] = {1, 0, -1, 0}; // NORTH, EAST, SOUTH, WEST
    
    for (const char *c = commands; *c != '\0'; c++)
    {
        switch (*c)
        {
        case 'R':
            robot->direction = (robot->direction + 1) & 3;
            break;
        case 'L':
            robot->direction = (robot->direction + 3) & 3;
            break;
        default: // Advance
            robot->position.x += dx[robot->direction];
            robot->position.y += dy[robot->direction];
            break;
        }
    }
}