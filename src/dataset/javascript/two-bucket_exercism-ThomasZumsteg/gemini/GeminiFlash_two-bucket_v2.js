var TwoBucket = function(sizeOne, sizeTwo, goal, starterBucket) {
    this.bucketOneSize = sizeOne;
    this.bucketTwoSize = sizeTwo;
    this.goal = goal;
    this.starterBucket = starterBucket;
};

TwoBucket.prototype.moves = function() {
    let moves = 0;
    let bucketOne = 0;
    let bucketTwo = 0;
    let goalBucketSize = this.starterBucket === 'one' ? this.bucketOneSize : this.bucketTwoSize;
    let otherBucketSize = this.starterBucket === 'one' ? this.bucketTwoSize : this.bucketOneSize;
    let firstBucket = this.starterBucket === 'one' ? 1 : 2;

    while (bucketOne !== this.goal && bucketTwo !== this.goal) {
        moves++;

        if (this.starterBucket === 'one') {
            if (bucketOne === 0) {
                bucketOne = this.bucketOneSize;
            } else if (bucketTwo === this.bucketTwoSize) {
                bucketTwo = 0;
            } else {
                const pourAmount = Math.min(bucketOne, this.bucketTwoSize - bucketTwo);
                bucketTwo += pourAmount;
                bucketOne -= pourAmount;
            }
        } else {
            if (bucketTwo === 0) {
                bucketTwo = this.bucketTwoSize;
            } else if (bucketOne === this.bucketOneSize) {
                bucketOne = 0;
            } else {
                const pourAmount = Math.min(bucketTwo, this.bucketOneSize - bucketOne);
                bucketOne += pourAmount;
                bucketTwo -= pourAmount;
            }
        }

        if (bucketOne === this.goal || bucketTwo === this.goal) {
            break;
        }
    }

    this.goalBucketSize = (bucketOne === this.goal) ? this.bucketOneSize : this.bucketTwoSize;
    this.otherBucketSize = (bucketOne === this.goal) ? this.bucketTwoSize : this.bucketOneSize;
    this.goalBucket = (bucketOne === this.goal) ? 'one' : 'two';
    this.otherBucketContent = (bucketOne === this.goal) ? bucketTwo : bucketOne;

    return moves;
};

TwoBucket.prototype.goalBucketSize = function() {
    return this.goalBucketSize;
}

TwoBucket.prototype.otherBucket = function() {
    return this.otherBucketContent;
}

module.exports = TwoBucket;