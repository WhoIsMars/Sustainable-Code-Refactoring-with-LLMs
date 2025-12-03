class TwoBucket {
  constructor(sizeOne, sizeTwo, goal, starterBucket) {
    this.goalBucketSize = starterBucket === "one" ? sizeOne : sizeTwo;
    this.otherBucketSize = starterBucket === "one" ? sizeTwo : sizeOne;
    this.goal = goal;
  }

  moves() {
    let waterInGoal = 0;
    let otherBucket = 0;
    let moves = 0;

    while (waterInGoal !== this.goal) {
      moves++;
      if (waterInGoal === 0) {
        waterInGoal = this.goalBucketSize; // Fill goal bucket
      } else if (otherBucket === this.otherBucketSize) {
        otherBucket = 0; // Empty other bucket
      } else {
        const transferAmount = Math.min(waterInGoal, this.otherBucketSize - otherBucket);
        waterInGoal -= transferAmount;
        otherBucket += transferAmount;
      }
    }

    return moves;
  }
}

module.exports = TwoBucket;