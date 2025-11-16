// ovenTime returns the amount in minutes that the lasagna should stay in the
// oven.
constexpr int ovenTime() noexcept {
    return 40;
}

/* remainingOvenTime returns the remaining
   minutes based on the actual minutes already in the oven.
*/
constexpr int remainingOvenTime(int actualMinutesInOven) noexcept {
    return ovenTime() - actualMinutesInOven;
}

/* preparationTime returns an estimate of the preparation time based on the
   number of layers and the necessary time per layer.
*/
constexpr int preparationTime(int numberOfLayers) noexcept {
    constexpr int timePerLayer = 2;
    return timePerLayer * numberOfLayers;
}

// elapsedTime calculates the total time spent to create and bake the lasagna so
// far.
constexpr int elapsedTime(int numberOfLayers, int actualMinutesInOven) noexcept {
    return preparationTime(numberOfLayers) + actualMinutesInOven;
}