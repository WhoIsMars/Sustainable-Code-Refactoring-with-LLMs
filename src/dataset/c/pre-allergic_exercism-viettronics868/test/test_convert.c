/*
this is the test cases for pre-allergic exercise
Author LK
Date 2024-12-28
*/
#define _XOPEN_SOURCE 700 //define strdup() in GNU with glibc

#include "convert_2_result.h"
#include "test-framework/unity.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



void helper_test(int decimal_number, bool test_result);
void helper_test_allergen(int decimal_number, char *allergen);

void helper_test(int decimal_number, bool test_result){
    int array_binary[64] = {0};
   
    
    user_result user_record ;
   
    user_record.result = false;
    user_record.list_current_allergens[0] = strdup("EGG");
    user_record.list_current_allergens[1] = strdup("PEANUTS");
    user_record.list_current_allergens[2] = strdup("SHELLFISH");
    user_record.list_current_allergens[3] = strdup("STRAWBERRIES");
    user_record.list_current_allergens[4] = strdup("TOMATOES");
    user_record.list_current_allergens[5] = strdup("CHOCOLATE");
    user_record.list_current_allergens[6] = strdup("POLLEN");
    user_record.list_current_allergens[7] = strdup("CATS");

    decimal2binary(decimal_number, array_binary);
    return_result(array_binary, &user_record);

    TEST_ASSERT_EQUAL(test_result, user_record.result);
    
    for (size_t i = 0; i < 8; i++){
       
        {
            free(user_record.list_current_allergens[i]);
        }
        
    }
    

}

void helper_test_allergen(int decimal_number, char *allergen){
    int array_binary[64] = {0};
    
    user_result user_record;// = {false, {list_of_allergens}};
    
    user_record.result = false;
    user_record.list_current_allergens[0] = strdup("EGG");
    user_record.list_current_allergens[1] = strdup("PEANUTS");
    user_record.list_current_allergens[2] = strdup("SHELLFISH");
    user_record.list_current_allergens[3] = strdup("STRAWBERRIES");
    user_record.list_current_allergens[4] = strdup("TOMATOES");
    user_record.list_current_allergens[5] = strdup("CHOCOLATE");
    user_record.list_current_allergens[6] = strdup("POLLEN");
    user_record.list_current_allergens[7] = strdup("CATS");

    decimal2binary(decimal_number, array_binary);
    return_result(array_binary, &user_record);

    
    TEST_ASSERT_EQUAL_STRING(allergen, user_record.list_current_allergens[3]);

    for (size_t i = 0; i < 8; i++){
        free(user_record.list_current_allergens[i]);
    }

}



void setUp(void){

}

void tearDown(void){

}


static void test_convert_result(void){
    //TEST_IGNORE();
    helper_test(32, true);


}

static void test_convert_result_allergen(void){
    //TEST_IGNORE();
    helper_test_allergen(8, "STRAWBERRIES" );
}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_convert_result);
    RUN_TEST(test_convert_result_allergen);
    
    return UNITY_END();

}