var TwoBucket = function(sizeOne, sizeTwo, goal, starterBucket) {
	this.goalBucketSize = starterBucket === "one" ? sizeOne : sizeTwo;
	this.otherBucketSize = starterBucket === "one" ? sizeTwo : sizeOne;
	this.goal = goal;
}

TwoBucket.prototype.moves = function() {
	var waterInGoal = 0;
	var otherBucket = 0;
	var moves = 0;
	
	while (waterInGoal !== this.goal) {
		if (waterInGoal === 0) {
			waterInGoal = this.goalBucketSize;
		} else if (otherBucket === this.otherBucketSize) {
			otherBucket = 0;
		} else {
			var pourAmount = Math.min(waterInGoal, this.otherBucketSize - otherBucket);
			waterInGoal -= pourAmount;
			otherBucket += pourAmount;
		}
		moves++;
	}
	
	return moves;
};

module.exports = TwoBucket;