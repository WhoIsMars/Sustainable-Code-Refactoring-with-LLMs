constexpr int OVEN_TIME = 40;
constexpr int TIME_PER_LAYER = 2;

int ovenTime() {
    return OVEN_TIME;
}

int remainingOvenTime(int actualMinutesInOven) {
    return OVEN_TIME - actualMinutesInOven;
}

int preparationTime(int numberOfLayers) {
    return numberOfLayers * TIME_PER_LAYER;
}

int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return (numberOfLayers * TIME_PER_LAYER) + actualMinutesInOven;
}