#include "space_age.h"
#include <stdint.h>
#include <stdio.h>

float seconds_to_Earth_year(uint64_t seconds){
    float hours = seconds / 3600;
    float days = hours / 24;
    float weeks = days / 7;
    float years = weeks / 52;
    return years;
}

float planet_to_Earth_year(planet_t planet){
    float earth = 1.0;
    switch (planet){
        case MERCURY: {
            earth = earth * 0.2408467;
            break;}
        case VENUS: {
            earth = earth * 0.61519726;
            break;}
        case EARTH: {
            earth = earth * 1.0;
            break;}
        case MARS: {
            earth = earth * 1.8808158;
            break;}
        case JUPITER: {
            earth = earth * 11.862615;
            break;}
        case SATURN: {
            earth = earth * 29.447498;
            break;}
        case URANUS: {
            earth = earth * 84.016846;
            break;}
        case NEPTUNE: {
            earth = earth * 164.79132;
            break;}
        default: return -1;
        
    }
    return earth;
}

float age(planet_t planet, uint64_t seconds){
    if (planet_to_Earth_year(planet) == -1) return -1;
    else return(seconds_to_Earth_year(seconds) / planet_to_Earth_year(planet));
}




