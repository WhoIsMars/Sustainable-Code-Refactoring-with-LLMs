var Triangle = function(a, b, c) {
    if (a < 0 || b < 0 || c < 0) 
        throw "Only positive length sides are allowed";
    if (a === 0 || b === 0 || c === 0)
        throw "Triangle cannot have zero area";
    
    var sides = [a, b, c];
    sides.sort(function(x, y) { return x - y; });
    
    if (sides[0] + sides[1] <= sides[2])
        throw "Not a valid triangle";
    
    this.triangle = sides;
    
    if (sides[0] === sides[1] && sides[1] === sides[2])
        this._kind = "equilateral";
    else if (sides[0] === sides[1] || sides[1] === sides[2])
        this._kind = "isosceles";
    else
        this._kind = "scalene";
};

Triangle.prototype.kind = function() {
    return this._kind;
};

module.exports = Triangle;