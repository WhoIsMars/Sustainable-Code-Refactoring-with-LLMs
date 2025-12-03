#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
  return (robot_status_t){.direction = direction, .position = {.x = x, .y = y}};
}

void robot_move(robot_status_t *robot, const char *commands) {
  while (*commands) {
    switch (*commands) {
    case 'R':
      robot->direction = (robot->direction + 1) % DIRECTION_MAX;
      break;
    case 'L':
      robot->direction = (robot->direction == DIRECTION_DEFAULT)
                             ? DIRECTION_WEST
                             : robot->direction - 1;
      break;
    case 'A':
      switch (robot->direction) {
      case DIRECTION_NORTH:
        robot->position.y++;
        break;
      case DIRECTION_SOUTH:
        robot->position.y--;
        break;
      case DIRECTION_EAST:
        robot->position.x++;
        break;
      case DIRECTION_WEST:
        robot->position.x--;
        break;
      }
      break;
    }
    commands++;
  }
}