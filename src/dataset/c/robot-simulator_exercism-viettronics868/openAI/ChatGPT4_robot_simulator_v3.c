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

void deploy_from_north(robot_status_t *robot, const char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_WEST; break;
        case 'R': robot->direction = DIRECTION_EAST; break;
        case 'A': robot->position.y += 1; break;
    }
}

void deploy_from_east(robot_status_t *robot, const char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_NORTH; break;
        case 'R': robot->direction = DIRECTION_SOUTH; break;
        case 'A': robot->position.x += 1; break;
    }
}

void deploy_from_south(robot_status_t *robot, const char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_EAST; break;
        case 'R': robot->direction = DIRECTION_WEST; break;
        case 'A': robot->position.y -= 1; break;
    }
}

void deploy_from_west(robot_status_t *robot, const char input) {
    switch (input) {
        case 'L': robot->direction = DIRECTION_SOUTH; break;
        case 'R': robot->direction = DIRECTION_NORTH; break;
        case 'A': robot->position.x -= 1; break;
    }
}

void robot_move(robot_status_t *robot, const char *command) {
    if (!robot || !command) return;

    static const struct {
        void (*robot_state)(robot_status_t *robot, const char input);
        const char *description;
    } lk_robot[] = {
        {deploy_from_north, "void deploy_from_north(robot_status_t *, const char)"},
        {deploy_from_east, "void deploy_from_east(robot_status_t *, const char)"},
        {deploy_from_south, "void deploy_from_south(robot_status_t *, const char)"},
        {deploy_from_west, "void deploy_from_west(robot_status_t *, const char)"}
    };

    size_t leng_command = strlen(command);
    for (size_t j = 0; j < leng_command; j++) {
        char input = command[j];
        if (input == 'L' || input == 'R' || input == 'A') {
            lk_robot[robot->direction].robot_state(robot, input);
            printf("%s \n", lk_robot[robot->direction].description);
        }
    }
}