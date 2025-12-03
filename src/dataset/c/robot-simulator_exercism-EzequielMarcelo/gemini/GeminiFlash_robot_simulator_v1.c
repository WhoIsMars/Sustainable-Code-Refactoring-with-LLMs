#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    return (robot_status_t){direction, {x, y}};
}

void turn_left(robot_status_t *robot) {
    robot->direction = (robot->direction == DIRECTION_NORTH) ? DIRECTION_WEST : (robot->direction - 1);
}

void turn_right(robot_status_t *robot) {
    robot->direction = (robot->direction == DIRECTION_WEST) ? DIRECTION_NORTH : (robot->direction + 1);
}

void advance(robot_status_t *robot) {
    switch (robot->direction) {
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
    }
}

void robot_move(robot_status_t *robot, const char *commands) {
    for (const char *command = commands; *command != '\0'; ++command) {
        if (*command == 'R') {
            turn_right(robot);
        } else if (*command == 'L') {
            turn_left(robot);
        } else if (*command == 'A') {
            advance(robot);
        }
    }
}