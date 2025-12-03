/*
this is an exercise from Exercism framework. I applied BIG-O notation on my data structure.
I tried to apply O(1) for this algorithm.
Author L.K
Date 2024-12-03
*/
#include "robot_simulator.h"
#include <stdio.h>
#include <string.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y){
    robot_status_t robot_init = {
        .direction = direction,
        .position.x = x,
        .position.y = y
    };
    return robot_init;
}

void robot_move(robot_status_t *robot, const char *command){
    if (!robot || !command) return;

    size_t command_length = strlen(command);

    for (size_t i = 0; i < command_length; ++i) {
        switch (robot->direction) {
            case DIRECTION_NORTH:
                if (command[i] == 'L') {
                    robot->direction = DIRECTION_WEST;
                } else if (command[i] == 'R') {
                    robot->direction = DIRECTION_EAST;
                } else if (command[i] == 'A') {
                    robot->position.y += 1;
                }
                break;
            case DIRECTION_EAST:
                if (command[i] == 'L') {
                    robot->direction = DIRECTION_NORTH;
                } else if (command[i] == 'R') {
                    robot->direction = DIRECTION_SOUTH;
                } else if (command[i] == 'A') {
                    robot->position.x += 1;
                }
                break;
            case DIRECTION_SOUTH:
                if (command[i] == 'L') {
                    robot->direction = DIRECTION_EAST;
                } else if (command[i] == 'R') {
                    robot->direction = DIRECTION_WEST;
                } else if (command[i] == 'A') {
                    robot->position.y -= 1;
                }
                break;
            case DIRECTION_WEST:
                if (command[i] == 'L') {
                    robot->direction = DIRECTION_SOUTH;
                } else if (command[i] == 'R') {
                    robot->direction = DIRECTION_NORTH;
                } else if (command[i] == 'A') {
                    robot->position.x -= 1;
                }
                break;
            default:
                // Handle invalid direction (optional)
                break;
        }
    }
}