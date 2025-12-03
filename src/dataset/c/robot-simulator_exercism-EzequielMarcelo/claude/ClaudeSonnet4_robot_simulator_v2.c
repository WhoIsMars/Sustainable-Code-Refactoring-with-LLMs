#include "robot_simulator.h"

// Direction vectors for movement: North, East, South, West
static const int dx[] = {0, 1, 0, -1};
static const int dy[] = {1, 0, -1, 0};

robot_status_t robot_create(robot_direction_t direction, int x, int y) 
{
    robot_status_t robot;
    robot.direction = direction;
    robot.position.x = x;
    robot.position.y = y;
    return robot;
}

static inline void turn_left(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 3) & 3;
}

static inline void turn_right(robot_status_t *robot) 
{
    robot->direction = (robot->direction + 1) & 3;
}

static inline void advance(robot_status_t *robot) 
{
    robot->position.x += dx[robot->direction];
    robot->position.y += dy[robot->direction];
}

void robot_move(robot_status_t *robot, const char *commands) 
{
    for (const char *command = commands; *command; command++) 
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
        }
    }
}