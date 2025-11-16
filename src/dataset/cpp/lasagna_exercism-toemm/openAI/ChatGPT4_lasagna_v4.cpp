constexpr int OVEN_TIME = 40;

int ovenTime() {
    return OVEN_TIME;
}

int remainingOvenTime(int actualMinutesInOven) {
    return OVEN_TIME - actualMinutesInOven;
}

constexpr int PREPARATION_TIME_PER_LAYER = 2;

int preparationTime(int numberOfLayers) {
    return numberOfLayers * PREPARATION_TIME_PER_LAYER;
}

int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return (numberOfLayers * PREPARATION_TIME_PER_LAYER) + actualMinutesInOven;
}