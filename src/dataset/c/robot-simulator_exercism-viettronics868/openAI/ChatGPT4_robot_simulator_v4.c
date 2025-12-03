#include "robot_simulator.h"
#include <stdio.h>
#include <string.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    return (robot_status_t){
        .direction = direction,
        .position = { .x = x, .y = y }
    };
}

void deploy_from_north(robot_status_t *robot, char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_WEST; break;
        case 'R': robot->direction = DIRECTION_EAST; break;
        case 'A': robot->position.y += 1; break;
    }
}

void deploy_from_east(robot_status_t *robot, char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_NORTH; break;
        case 'R': robot->direction = DIRECTION_SOUTH; break;
        case 'A': robot->position.x += 1; break;
    }
}

void deploy_from_south(robot_status_t *robot, char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_EAST; break;
        case 'R': robot->direction = DIRECTION_WEST; break;
        case 'A': robot->position.y -= 1; break;
    }
}

void deploy_from_west(robot_status_t *robot, char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_SOUTH; break;
        case 'R': robot->direction = DIRECTION_NORTH; break;
        case 'A': robot->position.x -= 1; break;
    }
}

void robot_move(robot_status_t *robot, const char *command) {
    if (!robot || !command) return;

    static void (*robot_states[])(robot_status_t *, char) = {
        deploy_from_north,
        deploy_from_east,
        deploy_from_south,
        deploy_from_west
    };

    for (size_t i = 0; command[i] != '\0'; ++i) {
        char input = command[i];
        if (input == 'L' || input == 'R' || input == 'A') {
            robot_states[robot->direction](robot, input);
        }
    }
}