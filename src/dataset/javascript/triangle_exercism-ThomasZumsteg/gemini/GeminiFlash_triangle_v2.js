/* Classifies triangles */
var Triangle = function(a,b,c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw "Only positive length sides are allowed";
    }

    this.triangle = [a,b,c].sort((x, y) => x - y);
    
    if (this.triangle[0] + this.triangle[1] <= this.triangle[2]) {
        throw "Not a valid triangle";
    }
}

Triangle.prototype.kind = function() {
	/* Determines the type of triangle */

	// Sides from smallest to largest
	var a = this.triangle[0];
	var b = this.triangle[1];
	var c = this.triangle[2];

	// Classification
	if (a === b) {
        if (b === c) {
            return "equilateral";
        } else {
            return "isosceles";
        }
    } else if (b === c) {
        return "isosceles";
    } else {
        return "scalene";
    }
};

module.exports = Triangle;