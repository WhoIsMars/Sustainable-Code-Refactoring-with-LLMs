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

//this function will deploy robot from direction north
void deploy_from_north(robot_status_t *robot, const char input){
    if (input == 'L'){
        robot->direction = DIRECTION_WEST;
    } else if (input == 'R'){
        robot->direction = DIRECTION_EAST;
    } else {
        robot->position.y += 1;
    }
}

//this function will deploy robot from direction east
void deploy_from_east(robot_status_t *robot, const char input){
    if (input == 'L'){
        robot->direction = DIRECTION_NORTH;
    } else if (input == 'R'){
        robot->direction = DIRECTION_SOUTH;
    } else {
        robot->position.x += 1;
    }
}

//this function will deploy robot from direction south
void deploy_from_south(robot_status_t *robot, const char input){
    if (input == 'L'){
        robot->direction = DIRECTION_EAST;
    } else if (input == 'R'){
        robot->direction = DIRECTION_WEST;
    } else {
        robot->position.y -= 1;
    }
}

//this function will deploy robot from direction west
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
    const char *descriptor[] = {//this array of pointer will show the name of the function was called
        "void deploy_from_north(robot_status_t *, const char)", 
        "void deploy_from_east(robot_status_t *, const char)", 
        "void deploy_from_south(robot_status_t *, const char)",
        "void deploy_from_west(robot_status_t *, const char)"
    };

    typedef struct{  //declare a struct including the array of function pointer and descriptor
        void (*robot_state)(robot_status_t *robot, const char input);
        const char *description;
    }robot_state_descrip_t;

    robot_state_descrip_t lk_robot[4] = { //declare an array of robot_state_descrip_t and initialize it
        {deploy_from_north, descriptor[0]},
        {deploy_from_east, descriptor[1]},
        {deploy_from_south, descriptor[2]},
        {deploy_from_west, descriptor[3]}
    };

    const char *letter_command[] = {"L", "R", "A"};
    

    if ((robot != NULL) && (command != NULL)){
        size_t leng_command = strlen(command);
        for (robot_direction_t i = DIRECTION_NORTH; i < DIRECTION_MAX; i++){
            if (robot->direction == i){ //check the direction of robot
                for (size_t j = 0; j < leng_command; j++){ //traverse each letter of the command
                    for (size_t k = 0; k < 3; k++){ //pick the right letter from the list of letters
                        if (command[j] == *letter_command[k]){
                            lk_robot[robot->direction]
                                .robot_state
                                    (robot, *letter_command[k]);
                            //this line of code show the name of function was called
                            printf("%s \n", lk_robot[robot->direction]
                                                .description);
                            break;//exit the 'for' loop of k
                        }      
                    }
                }
                break; //exit the 'for' loop of i
            }
        }
    }
    


}