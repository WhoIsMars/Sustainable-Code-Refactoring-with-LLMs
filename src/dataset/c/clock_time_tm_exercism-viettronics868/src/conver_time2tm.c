#include <time.h>
#include <stdio.h>
#include "conver_time2tm.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int cumulate_day_reg[13]      = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

int cumulate_day_leap[13]     = {1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336, 367};
int array_of_cummulate_days[13];

bool is_leap_year(int year){
    return((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}



tm_lk *localtime_lk(time_lk *time_utc){
    if (time_utc == NULL){
        fprintf(stderr, "time input is invalid - error code: %s \n", strerror(errno));
        return NULL;
    }

    printf("utc time is %ld \n", *time_utc);

    static tm_lk *tm_n;
    tm_n = malloc(sizeof(tm_lk));
    if (tm_n == NULL){
        fprintf(stderr, "memory allocation error - error code: %s \n", strerror(errno));
        return NULL;
    }
    memset(tm_n, 0, sizeof(tm_lk));
    
    time_lk time_n = (*time_utc) - TORONTO_OFFSET_IN_SECONDS;//hardcode time zone in Toronto - UTC-4:00

    printf("toronto time is %ld \n", time_n);

    int year_count = 0;
    int month_count = 0;
    int day_count =0;

    tm_n->tm_sec  = time_n % 60;                //seconds past current minute
    tm_n->tm_min  = (time_n / SECONDS_IN_MIN) % 60;         //minutes past current hour
    tm_n->tm_hour = (time_n / SECONDS_IN_HOUR) % 24;      //hours past current day
    
    convert_time2yearmonthday(&time_n, &year_count, &month_count, &day_count );
    
    tm_n->tm_year = year_count;
    tm_n->tm_mon = month_count;
    tm_n->tm_mday = day_count;

    return tm_n;

    
}

void convert_time2yearmonthday(time_lk *time_by_second_local, int *year, int *month, int *day){
    if (time_by_second_local == NULL){
        fprintf(stderr, "input time is invalid - error code %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int year_in_calculate = EPOCH;
    
    int time_by_days = (*time_by_second_local)/SECONDS_IN_DAY;
    int days_in_year = 0;
    int remaining_days_for_next_year = 0;
    
    while (1){// this while loop for calculating year
        
        days_in_year = (is_leap_year(year_in_calculate)) ? 366 :  365;
        printf("in year %d has %d days \n", year_in_calculate, days_in_year);
        
        if (time_by_days >= days_in_year){
            time_by_days -= days_in_year; 
            printf("after a year, days leave %d \n", time_by_days);
        }
        else {
                remaining_days_for_next_year = time_by_days;
                
                printf("after year %d the remaining days for next year is %d \n",
                        year_in_calculate, 
                        remaining_days_for_next_year);
                break;
        }
        year_in_calculate++;
       
    }
    *year = year_in_calculate;//calculating the year
    int year_after = year_in_calculate + 1;
    
    int array_of_cummulate_days[13] = {0};
    memcpy(array_of_cummulate_days, 
            (is_leap_year(year_after)) ? cumulate_day_leap : cumulate_day_reg, 
            sizeof(array_of_cummulate_days));

   
    if (remaining_days_for_next_year > 0){
        for (int i = 0; i < 12; i++){//this for loop for calculating month and day
            if (remaining_days_for_next_year >= array_of_cummulate_days[i] && 
                remaining_days_for_next_year < array_of_cummulate_days[i+1]){
                    
                    *month = i;
                    *day = remaining_days_for_next_year - array_of_cummulate_days[i] + 2 ;
                    printf("remaining days between month %d and %d is %d \n", 
                            i, 
                            i+1, 
                            remaining_days_for_next_year);
                    break;
                }
           
        }
    }
}

