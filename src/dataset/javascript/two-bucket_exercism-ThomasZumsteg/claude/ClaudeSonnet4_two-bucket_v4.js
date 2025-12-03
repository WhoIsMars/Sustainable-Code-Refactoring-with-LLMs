var TwoBucket = function(sizeOne, sizeTwo, goal, starterBucket) {
	this.goalBucketSize = starterBucket === "one" ? sizeOne : sizeTwo;
	this.otherBucketSize = starterBucket === "one" ? sizeTwo : sizeOne;
	this.goalBucket = starterBucket;
	this.goal = goal;
};

TwoBucket.prototype.moves = function() {
	var waterInGoal = 0;
	var otherBucket = 0;
	var moves = 0;
	var goal = this.goal;
	var goalBucketSize = this.goalBucketSize;
	var otherBucketSize = this.otherBucketSize;
	
	while (goal !== waterInGoal) {
		moves++;
		
		if (waterInGoal === 0) {
			waterInGoal = goalBucketSize;
		} else if (otherBucket === otherBucketSize) {
			otherBucket = 0;
		} else {
			var spaceInOther = otherBucketSize - otherBucket;
			if (waterInGoal <= spaceInOther) {
				otherBucket += waterInGoal;
				waterInGoal = 0;
			} else {
				waterInGoal -= spaceInOther;
				otherBucket = otherBucketSize;
			}
		}
	}
	
	return moves;
};

module.exports = TwoBucket;