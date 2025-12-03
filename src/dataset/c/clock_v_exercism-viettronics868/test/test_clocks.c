#include "clocks_v.h"
#include <stdio.h>
#include "test-framework/unity.h"
#include "time_v.h"

clock_t create_clocks_helper(double hour, double minute);


void compare_helper(bool expected, double a_hour, double a_minute, double b_hour, double b_minute);

clock_t create_clocks_helper(double hour, double minute){

    return create_clocks(hour, minute);

}


static void test_create_clock(void){
    //TEST_IGNORE();

    clock_t new_clock = create_clocks_helper(25, 20);

    
    TEST_ASSERT_EQUAL_STRING("01:20", new_clock.text);   

}

static void test_add_minutes(void){
    //TEST_IGNORE();
    clock_t clock1 = create_clocks_helper(22, 28);
    clock_t clock_mod = add_minute(clock1, 2);
    TEST_ASSERT_EQUAL_STRING("22:30", clock_mod.text);
}

void compare_helper(bool expected, double a_hour, double a_minute, double b_hour, double b_minute){
    clock_t clock1 = create_clocks_helper(a_hour, a_minute);
    clock_t clock2 = create_clocks_helper(b_hour, b_minute);
    bool actual =  clock_is_equal(clock1, clock2);

    if (expected){
        TEST_ASSERT_TRUE(actual);
    }
    else {
        TEST_ASSERT_FALSE(actual);
    }
}

static void test_compare_clocks(void){
    double a_hour = 2;
    double a_minute = 22;
    double b_hour = 2;
    double b_minute = 22;
    bool expected = true;

    compare_helper(expected, a_hour, a_minute, b_hour, b_minute);
}

void setUp(void){

}

void tearDown(void){

}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_create_clock);
    RUN_TEST(test_add_minutes);
    RUN_TEST(test_compare_clocks);

    return UNITY_END();

}