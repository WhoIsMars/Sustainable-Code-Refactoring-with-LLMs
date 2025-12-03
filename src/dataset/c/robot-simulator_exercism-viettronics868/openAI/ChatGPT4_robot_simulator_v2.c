#include "robot_simulator.h"
#include <stdio.h>
#include <string.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    return (robot_status_t){
        .direction = direction,
        .position.x = x,
        .position.y = y
    };
}

void deploy_robot(robot_status_t *robot, const char input) {
    static const robot_direction_t left_turn[] = {
        DIRECTION_WEST, DIRECTION_NORTH, DIRECTION_EAST, DIRECTION_SOUTH
    };
    static const robot_direction_t right_turn[] = {
        DIRECTION_EAST, DIRECTION_SOUTH, DIRECTION_WEST, DIRECTION_NORTH
    };
    static const int move_x[] = {0, 1, 0, -1};
    static const int move_y[] = {1, 0, -1, 0};

    if (input == 'L') {
        robot->direction = left_turn[robot->direction];
    } else if (input == 'R') {
        robot->direction = right_turn[robot->direction];
    } else if (input == 'A') {
        robot->position.x += move_x[robot->direction];
        robot->position.y += move_y[robot->direction];
    }
}

void robot_move(robot_status_t *robot, const char *command) {
    if (robot == NULL || command == NULL) {
        return;
    }

    size_t leng_command = strlen(command);
    for (size_t j = 0; j < leng_command; j++) {
        deploy_robot(robot, command[j]);
    }
}