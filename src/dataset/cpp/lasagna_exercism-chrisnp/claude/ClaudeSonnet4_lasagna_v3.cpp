constexpr int BAKING_TIME = 40;
constexpr int LAYER_PREP = 2;

constexpr int ovenTime() noexcept {
    return BAKING_TIME;
}

constexpr int remainingOvenTime(int actualMinutesInOven) noexcept {
    return BAKING_TIME - actualMinutesInOven;
}

constexpr int preparationTime(int numberOfLayers) noexcept {
    return LAYER_PREP * numberOfLayers; 
}

constexpr int elapsedTime(int numberOfLayers, int actualMinutesInOven) noexcept {
    return LAYER_PREP * numberOfLayers + actualMinutesInOven;
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif