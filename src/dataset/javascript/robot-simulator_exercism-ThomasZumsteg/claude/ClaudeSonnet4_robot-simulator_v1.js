/* A robot to that follows simple instructions */
var Robot = function() {
    this.bearing = 'north';
    this.coordinates = [0, 0];
    this.bearingIndex = 0;
}

// Directions the robot can face and associated vectors
var directions = [ 'north', 'east', 'south', 'west' ];
var vectors = [[0, 1], [1, 0], [0, -1], [-1, 0]];

// Pre-computed direction lookup for O(1) access
var directionMap = {
    'north': 0,
    'east': 1,
    'south': 2,
    'west': 3
};

Robot.prototype.orient = function(direction) {
    /* Sets the direction of the robot */
    var index = directionMap[direction];
    if(index === undefined)
        throw "Invalid Robot Bearing";
    this.bearing = direction;
    this.bearingIndex = index;
};

Robot.prototype.turnRight = function() {
    /* Changes the bearing one step to the right */
    this.bearingIndex = (this.bearingIndex + 1) & 3;
    this.bearing = directions[this.bearingIndex];
};

Robot.prototype.turnLeft = function() {
    /* Changes the bearing one step to the left */
    this.bearingIndex = (this.bearingIndex + 3) & 3;
    this.bearing = directions[this.bearingIndex];
};

/* Sets the robots position */
Robot.prototype.at = function(x, y) { 
    this.coordinates[0] = x;
    this.coordinates[1] = y;
};

Robot.prototype.advance = function() {
    /* Move the position one step in the direction the robot is facing */
    var vector = vectors[this.bearingIndex];
    this.coordinates[0] += vector[0];
    this.coordinates[1] += vector[1];
};

// Instructions the robot understands
var instructionMap = {
    'L': Robot.prototype.turnLeft,
    'R': Robot.prototype.turnRight,
    'A': Robot.prototype.advance,
};

Robot.prototype.instructions = function(instruction_list) {
    /* Make a list of instructions from a string */
    var result = new Array(instruction_list.length);
    for(var i = 0; i < instruction_list.length; i++) {
        result[i] = instructionMap[instruction_list[i]];
    }
    return result;
};

Robot.prototype.place = function(args) {
    /* Initilized the direction and location of a robot */
    this.orient(args['direction']);
    this.at(args['x'], args['y']);
};

Robot.prototype.evaluate = function(instruction_list) {
    /* Robot preforms a series of instructions */
    for(var i = 0; i < instruction_list.length; i++) {
        instructionMap[instruction_list[i]].call(this);
    }
};

module.exports = Robot;
exports.directions = directions;