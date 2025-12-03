//this is a function to test the coversion the time of seconds to a custom struct tm_lk
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "conver_time2tm.h"
#include <time.h>
#include "test-framework/unity.h"
#include <string.h>

void helper_test_year(time_t *sec_val);
void helper_test_month(time_t *sec_val);
void helper_test_day(time_t *sec_val);
void helper_test_localtime_lk(time_t *sec_val);

void setUp(void){

}

void tearDown(void){

}

void helper_test_year(time_t *sec_val){

    struct tm *tm_origin = localtime(sec_val);
    struct tm_lk *tm_mod = localtime_lk(sec_val);//need to free this memory
    if (tm_origin == NULL || tm_mod == NULL){
        fprintf(stderr, "conversion time error-error code %s \n", strerror(errno));
        free(tm_mod);
        exit(EXIT_FAILURE);
    }
    
    tm_origin->tm_year += 1900;
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(tm_origin->tm_year, tm_mod->tm_year, "Year values do not match");

    free(tm_mod);
}

void helper_test_month(time_t *sec_val){

    struct tm *tm_origin = localtime(sec_val);
    if (tm_origin == NULL){
        fprintf(stderr, "cannot convert time to struct tm-error code : %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct tm_lk *tm_mod = localtime_lk(sec_val);
    if (tm_mod == NULL){
        fprintf(stderr, "cannot convert time_lk to struct tm_lk- error code %s", strerror(errno));
        free(tm_mod);
        exit(EXIT_FAILURE);
    }

    TEST_ASSERT_EQUAL_INT_MESSAGE(tm_origin->tm_mon, tm_mod->tm_mon, "value doesn't match");
    free(tm_mod);
}

 void helper_test_day(time_t *sec_val){

    struct tm *tm_origin = localtime(sec_val);
    if (tm_origin == NULL){
        fprintf(stderr, "cannot convert time_t to struct tm-error code %s", strerror(errno));
        
        exit(EXIT_FAILURE);
    }

    struct tm_lk *tm_mod = localtime_lk(sec_val);
    if (tm_mod == NULL){
        fprintf(stderr, "cannot convert time_lk to struct tm_lk");
        free(tm_mod);
        exit(EXIT_FAILURE);
    }

    TEST_ASSERT_EQUAL_INT_MESSAGE(tm_origin->tm_mday, tm_mod->tm_mday, "value doesn't match");
    free(tm_mod);
}

void helper_test_localtime_lk(time_t *sec_val){
    struct tm *tm_origin = localtime(sec_val);
    if (tm_origin == NULL){
        fprintf(stderr, "cannot convert time_t to struct tm-error code %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    tm_origin->tm_year += 1900;
    struct tm_lk *tm_mod = localtime_lk(sec_val);
    if (tm_mod == NULL){ 
        fprintf(stderr, "cannot convert time_t to struct tm- error code %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    //tm_mod->tm_year += 1970;
    char str_origin[64] = {0};
    char str_mod[64] = {0};
    snprintf(str_origin, 64, "%d-%d-%d %d:%d:%d",tm_origin->tm_year,
                                                    tm_origin->tm_mon,
                                                    tm_origin->tm_mday,
                                                    tm_origin->tm_hour,
                                                    tm_origin->tm_min,
                                                    tm_origin->tm_sec);

    snprintf(str_mod, 64, "%d-%d-%d %d:%d:%d",   tm_mod->tm_year,
                                                    tm_mod->tm_mon,
                                                    tm_mod->tm_mday,
                                                    tm_mod->tm_hour,
                                                    tm_mod->tm_min,
                                                    tm_mod->tm_sec);
    
    TEST_ASSERT_EQUAL_STRING(str_origin, str_mod);

    free(tm_mod);


}

static void test_year(void){
    //TEST_IGNORE();
    time_t value = 1000000;
    helper_test_year(&value);

}

static void test_month(void){
    //TEST_IGNORE();
    time_t value = 4000000;
    helper_test_month(&value);

}

static void test_day(void){
    //TEST_IGNORE();
    time_t value = 10000000;
    helper_test_day(&value);
}

static void test_localtime_lk(void){
    //TEST_IGNORE();
    time_t value = 100000000;
    helper_test_localtime_lk(&value);
}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(test_year);
    RUN_TEST(test_month);
    RUN_TEST(test_day);
    RUN_TEST(test_localtime_lk);

    return UNITY_END();

}