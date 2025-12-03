#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    return (robot_status_t){direction, {x, y}};
}

void robot_move(robot_status_t *robot, const char *commands) {
    while (*commands) {
        switch (*commands++) {
        case 'R':
            robot->direction = (robot->direction + 1) % 4;
            break;
        case 'L':
            robot->direction = (robot->direction + 3) % 4;
            break;
        default:
            if (robot->direction == DIRECTION_NORTH) {
                robot->position.y++;
            } else if (robot->direction == DIRECTION_EAST) {
                robot->position.x++;
            } else if (robot->direction == DIRECTION_SOUTH) {
                robot->position.y--;
            } else {
                robot->position.x--;
            }
        }
    }
}