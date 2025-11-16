const int BAKING_TIME = 40;
const int LAYER_PREP = 2;

int ovenTime() {
    return BAKING_TIME;
}

int remainingOvenTime(int actualMinutesInOven) {
    return BAKING_TIME - actualMinutesInOven;
}

int preparationTime(int numberOfLayers) {
    return LAYER_PREP * numberOfLayers; 
}

int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return preparationTime(numberOfLayers) + actualMinutesInOven;
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif