int ovenTime() {
    return 40;
}

int remainingOvenTime(int actualMinutesInOven) {
    return 40 - actualMinutesInOven;
}

int preparationTime(int numberOfLayers) {
    return numberOfLayers << 1; // Multiply by 2 using bitwise shift for efficiency
}

int elapsedTime(int numberOfLayers, int actualMinutesInOven) {
    return (numberOfLayers << 1) + actualMinutesInOven; // Inline preparationTime for efficiency
}