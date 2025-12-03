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

void robot_move(robot_status_t *robot, const char *command) {
    if (!robot || !command) return;

    static const struct {
        int dx, dy;
        robot_direction_t left, right;
        const char *description;
    } directions[DIRECTION_MAX] = {
        {0, 1, DIRECTION_WEST, DIRECTION_EAST, "void deploy_from_north(robot_status_t *, const char)"},
        {1, 0, DIRECTION_NORTH, DIRECTION_SOUTH, "void deploy_from_east(robot_status_t *, const char)"},
        {0, -1, DIRECTION_EAST, DIRECTION_WEST, "void deploy_from_south(robot_status_t *, const char)"},
        {-1, 0, DIRECTION_SOUTH, DIRECTION_NORTH, "void deploy_from_west(robot_status_t *, const char)"}
    };

    size_t leng_command = strlen(command);
    for (size_t i = 0; i < leng_command; i++) {
        char input = command[i];
        switch (input) {
            case 'L':
                robot->direction = directions[robot->direction].left;
                break;
            case 'R':
                robot->direction = directions[robot->direction].right;
                break;
            case 'A':
                robot->position.x += directions[robot->direction].dx;
                robot->position.y += directions[robot->direction].dy;
                break;
            default:
                continue;
        }
        printf("%s \n", directions[robot->direction].description);
    }
}