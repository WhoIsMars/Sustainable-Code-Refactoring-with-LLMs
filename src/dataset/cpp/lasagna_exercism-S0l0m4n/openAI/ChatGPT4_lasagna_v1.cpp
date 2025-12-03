constexpr int OVEN_TIME = 40;

int ovenTime() {
    return OVEN_TIME;
}

int remainingOvenTime(int actualMinutesInOven) {
    return OVEN_TIME - actualMinutesInOven;
}

int preparationTime(int numberOfLayers) {
    return numberOfLayers << 1; // Multiply by 2 using bitwise shift for efficiency
}

int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return (numberOfLayers << 1) + actualMinutesInOven;
}