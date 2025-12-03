#include "robot_simulator.h"

inline void turn_left(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 3) & 3; // Use bitwise AND for modulo 4
}

inline void turn_right(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 1) & 3; // Use bitwise AND for modulo 4
}

inline void advance(robot_status_t *robot) 
{
    static const int dx[] = {0, 1, 0, -1}; // Precomputed direction deltas
    static const int dy[] = {1, 0, -1, 0};
    robot->position.x += dx[robot->direction];
    robot->position.y += dy[robot->direction];
}

robot_status_t robot_create(robot_direction_t direction, int x, int y) 
{
    return (robot_status_t){.direction = direction, .position = {x, y}};
}

void robot_move(robot_status_t *robot, const char *commands) 
{
    while (*commands) 
    {
        switch (*commands++) 
        {
            case 'R': turn_right(robot); break;
            case 'L': turn_left(robot); break;
            case 'A': advance(robot); break;
        }
    }
}