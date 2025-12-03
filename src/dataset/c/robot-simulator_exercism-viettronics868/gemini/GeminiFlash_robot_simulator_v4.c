#include "robot_simulator.h"
#include <stdio.h>
#include <string.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    return (robot_status_t){.direction = direction, .position = {.x = x, .y = y}};
}

void robot_move(robot_status_t *robot, const char *command) {
    if (!robot || !command) return;

    static const char *descriptor[] = {
        "void deploy_from_north(robot_status_t *, const char)",
        "void deploy_from_east(robot_status_t *, const char)",
        "void deploy_from_south(robot_status_t *, const char)",
        "void deploy_from_west(robot_status_t *, const char)"};

    typedef void (*robot_state_func)(robot_status_t *, const char);

    static const robot_state_func move_functions[] = {
        [DIRECTION_NORTH] = [](robot_status_t *robot, const char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_WEST; break;
                case 'R': robot->direction = DIRECTION_EAST; break;
                case 'A': robot->position.y += 1; break;
            }
        },
        [DIRECTION_EAST] = [](robot_status_t *robot, const char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_NORTH; break;
                case 'R': robot->direction = DIRECTION_SOUTH; break;
                case 'A': robot->position.x += 1; break;
            }
        },
        [DIRECTION_SOUTH] = [](robot_status_t *robot, const char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_EAST; break;
                case 'R': robot->direction = DIRECTION_WEST; break;
                case 'A': robot->position.y -= 1; break;
            }
        },
        [DIRECTION_WEST] = [](robot_status_t *robot, const char input) {
            switch (input) {
                case 'L': robot->direction = DIRECTION_SOUTH; break;
                case 'R': robot->direction = DIRECTION_NORTH; break;
                case 'A': robot->position.x -= 1; break;
            }
        }
    };

    for (size_t i = 0; command[i] != '\0'; ++i) {
        if (command[i] == 'L' || command[i] == 'R' || command[i] == 'A') {
            move_functions[robot->direction](robot, command[i]);
            printf("%s \n", descriptor[robot->direction]);
        }
    }
}