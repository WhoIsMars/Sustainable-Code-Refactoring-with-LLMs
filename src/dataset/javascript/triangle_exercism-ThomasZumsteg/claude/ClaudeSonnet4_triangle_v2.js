/* Classifies triangles */
var Triangle = function(a,b,c) { 
    // Validate inputs early to avoid unnecessary sorting
    if (a <= 0 || b <= 0 || c <= 0) 
        throw "Only positive length sides are allowed";
    
    // Sort once during construction
    this.triangle = [a,b,c].sort((x,y) => x - y);
    
    // Cache validation results
    var min = this.triangle[0];
    var mid = this.triangle[1];
    var max = this.triangle[2];
    
    if (min + mid <= max)
        throw "Not a valid triangle";
}

Triangle.prototype.kind = function() {
    var a = this.triangle[0];
    var b = this.triangle[1];
    var c = this.triangle[2];

    // Use strict equality for faster comparison
    if (a === b) {
        return b === c ? "equilateral" : "isosceles";
    }
    
    return b === c ? "isosceles" : "scalene";
};

module.exports = Triangle;