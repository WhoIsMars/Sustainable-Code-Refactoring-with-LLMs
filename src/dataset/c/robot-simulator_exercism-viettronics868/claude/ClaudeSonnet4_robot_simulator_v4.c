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

static void (*const robot_functions[])(robot_status_t *, const char) = {
    deploy_from_north,
    deploy_from_east,
    deploy_from_south,
    deploy_from_west
};

static const char * const function_names[] = {
    "void deploy_from_north(robot_status_t *, const char)",
    "void deploy_from_east(robot_status_t *, const char)",
    "void deploy_from_south(robot_status_t *, const char)",
    "void deploy_from_west(robot_status_t *, const char)"
};

void robot_move(robot_status_t *robot, const char *command){
    if (!robot || !command) return;
    
    const char *cmd = command;
    while (*cmd) {
        if (*cmd == 'L' || *cmd == 'R' || *cmd == 'A') {
            robot_functions[robot->direction](robot, *cmd);
            printf("%s \n", function_names[robot->direction]);
        }
        cmd++;
    }
}