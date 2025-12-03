constexpr int OVEN_TIME = 40;
constexpr int TIME_PER_LAYER = 2;

inline int ovenTime() {
    return OVEN_TIME;
}

inline int remainingOvenTime(int actualMinutesInOven) {
    return OVEN_TIME - actualMinutesInOven;
}

inline int preparationTime(int numberOfLayers) {
    return TIME_PER_LAYER * numberOfLayers;
}

inline int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return (TIME_PER_LAYER * numberOfLayers) + actualMinutesInOven;
}