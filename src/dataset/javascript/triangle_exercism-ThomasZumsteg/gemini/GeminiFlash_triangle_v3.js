/* Classifies triangles */
var Triangle = function(a,b,c) {
    this.triangle = [a,b,c].sort((x, y) => x - y);
};

Triangle.prototype.kind = function() {
    var a = this.triangle[0];
    var b = this.triangle[1];
    var c = this.triangle[2];

    if (a <= 0) {
        throw "Only positive length sides are allowed";
    }

    if (a + b <= c) {
        throw "Not a valid triangle";
    }

    if (a === b) {
        if (b === c) {
            return "equilateral";
        }
        return "isosceles";
    } else if (b === c) {
        return "isosceles";
    }

    return "scalene";
};

module.exports = Triangle;