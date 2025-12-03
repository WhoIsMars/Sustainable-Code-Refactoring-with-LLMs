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

static inline void robot_turn_left(robot_status_t *robot) {
    robot->direction = (robot->direction + 3) & 3;
}

static inline void robot_turn_right(robot_status_t *robot) {
    robot->direction = (robot->direction + 1) & 3;
}

static inline void robot_advance(robot_status_t *robot) {
    static const int dx[] = {0, 1, 0, -1};
    static const int dy[] = {1, 0, -1, 0};
    
    robot->position.x += dx[robot->direction];
    robot->position.y += dy[robot->direction];
}

void robot_move(robot_status_t *robot, const char *command){
    if (!robot || !command) return;
    
    const char *cmd = command;
    while (*cmd) {
        switch (*cmd) {
            case 'L':
                robot_turn_left(robot);
                break;
            case 'R':
                robot_turn_right(robot);
                break;
            case 'A':
                robot_advance(robot);
                break;
        }
        cmd++;
    }
}