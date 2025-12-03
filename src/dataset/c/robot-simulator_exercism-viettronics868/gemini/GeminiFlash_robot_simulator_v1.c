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
    return (robot_status_t){.direction = direction, .position = {.x = x, .y = y}};
}

void robot_move(robot_status_t *robot, const char *command){
    if (!robot || !command) return;

    static const char *descriptor[] = {
        "void deploy_from_north(robot_status_t *, const char)",
        "void deploy_from_east(robot_status_t *, const char)",
        "void deploy_from_south(robot_status_t *, const char)",
        "void deploy_from_west(robot_status_t *, const char)"
    };

    typedef void (*robot_state_func)(robot_status_t *robot, char input);

    static robot_state_func robot_state_table[] = {
        [DIRECTION_NORTH] = [](robot_status_t *robot, char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_WEST; break;
                case 'R': robot->direction = DIRECTION_EAST; break;
                case 'A': robot->position.y += 1; break;
            }
        },
        [DIRECTION_EAST] = [](robot_status_t *robot, char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_NORTH; break;
                case 'R': robot->direction = DIRECTION_SOUTH; break;
                case 'A': robot->position.x += 1; break;
            }
        },
        [DIRECTION_SOUTH] = [](robot_status_t *robot, char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_EAST; break;
                case 'R': robot->direction = DIRECTION_WEST; break;
                case 'A': robot->position.y -= 1; break;
            }
        },
        [DIRECTION_WEST] = [](robot_status_t *robot, char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_SOUTH; break;
                case 'R': robot->direction = DIRECTION_NORTH; break;
                case 'A': robot->position.x -= 1; break;
            }
        }
    };

    for (size_t i = 0; command[i] != '\0'; ++i) {
        char input = command[i];
        if (input == 'L' || input == 'R' || input == 'A') {
            robot_state_table[robot->direction](robot, input);
            printf("%s \n", descriptor[robot->direction]);
        }
    }
}