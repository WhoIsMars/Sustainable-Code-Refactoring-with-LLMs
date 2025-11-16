constexpr int BAKING_TIME = 40;
constexpr int LAYER_PREP = 2;

inline int ovenTime() {
    return BAKING_TIME;
}

inline int remainingOvenTime(int actualMinutesInOven) {
    return BAKING_TIME - actualMinutesInOven;
}

inline int preparationTime(int numberOfLayers) {
    return LAYER_PREP * numberOfLayers;
}

inline int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return (LAYER_PREP * numberOfLayers) + actualMinutesInOven;
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif