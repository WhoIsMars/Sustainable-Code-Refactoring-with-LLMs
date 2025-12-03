var Triangle = function(a, b, c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw "Only positive length sides are allowed";
    }
    
    var min = a, mid = b, max = c;
    if (min > mid) { var temp = min; min = mid; mid = temp; }
    if (mid > max) { var temp = mid; mid = max; max = temp; }
    if (min > mid) { var temp = min; min = mid; mid = temp; }
    
    if (min + mid <= max) {
        throw "Not a valid triangle";
    }
    
    this.triangle = [min, mid, max];
};

Triangle.prototype.kind = function() {
    var a = this.triangle[0];
    var b = this.triangle[1];
    var c = this.triangle[2];
    
    if (a === b) {
        return b === c ? "equilateral" : "isosceles";
    }
    return b === c ? "isosceles" : "scalene";
};

module.exports = Triangle;