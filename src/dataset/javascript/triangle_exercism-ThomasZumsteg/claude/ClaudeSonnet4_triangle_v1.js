/* Classifies triangles */
var Triangle = function(a,b,c) { 
    // Sort once during construction and store directly
    if (a > b) { var temp = a; a = b; b = temp; }
    if (b > c) { var temp = b; b = c; c = temp; }
    if (a > b) { var temp = a; a = b; b = temp; }
    
    this.a = a;
    this.b = b;
    this.c = c;
}

Triangle.prototype.kind = function() {
    /* Determines the type of triangle */

    var a = this.a;
    var b = this.b;
    var c = this.c;

    // Validation - check most likely failures first
    if (a + b <= c)
        throw "Not a valid triangle";
    if (a <= 0)
        throw "Only positive length sides are allowed";
    if (a === 0 || b === 0 || c === 0)
        throw "Triangle cannot have zero area";

    // Classification - check most restrictive condition first
    if (a === b && b === c)
        return "equilateral";
    if (a === b || b === c)
        return "isosceles";
    return "scalene";
};

module.exports = Triangle;