constexpr int ovenTime() {
    return 40;
}

constexpr int preparationTimePerLayer = 2;

constexpr int remainingOvenTime(int actualMinutesInOven) {
    return ovenTime() - actualMinutesInOven;
}

constexpr int preparationTime(int numberOfLayers) {
    return preparationTimePerLayer * numberOfLayers;
}

constexpr int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return preparationTime(numberOfLayers) + actualMinutesInOven;
}