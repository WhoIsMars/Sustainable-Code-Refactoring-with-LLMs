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

void deploy_from_north(robot_status_t *robot, const char input){
    if (input == 'L'){
        robot->direction = DIRECTION_WEST;
    } else if (input == 'R'){
        robot->direction = DIRECTION_EAST;
    } else {
        robot->position.y += 1;
    }
}

void deploy_from_east(robot_status_t *robot, const char input){
    if (input == 'L'){
        robot->direction = DIRECTION_NORTH;
    } else if (input == 'R'){
        robot->direction = DIRECTION_SOUTH;
    } else {
        robot->position.x += 1;
    }
}

void deploy_from_south(robot_status_t *robot, const char input){
    if (input == 'L'){
        robot->direction = DIRECTION_EAST;
    } else if (input == 'R'){
        robot->direction = DIRECTION_WEST;
    } else {
        robot->position.y -= 1;
    }
}

void deploy_from_west(robot_status_t *robot, const char input){
    if (input == 'L'){
        robot->direction = DIRECTION_SOUTH;
    } else if (input == 'R'){
        robot->direction = DIRECTION_NORTH;
    } else {
        robot->position.x -= 1;
    }
}

void robot_move(robot_status_t *robot, const char *command){
    static const char* const descriptors[] = {
        "void deploy_from_north(robot_status_t *, const char)", 
        "void deploy_from_east(robot_status_t *, const char)", 
        "void deploy_from_south(robot_status_t *, const char)",
        "void deploy_from_west(robot_status_t *, const char)"
    };

    static void (*const robot_functions[])(robot_status_t *, const char) = {
        deploy_from_north,
        deploy_from_east,
        deploy_from_south,
        deploy_from_west
    };

    if (!robot || !command) return;

    const size_t command_length = strlen(command);
    void (*const current_function)(robot_status_t *, const char) = robot_functions[robot->direction];
    const char* const current_descriptor = descriptors[robot->direction];

    for (size_t i = 0; i < command_length; i++) {
        const char cmd = command[i];
        if (cmd == 'L' || cmd == 'R' || cmd == 'A') {
            current_function(robot, cmd);
            printf("%s \n", current_descriptor);
        }
    }
}