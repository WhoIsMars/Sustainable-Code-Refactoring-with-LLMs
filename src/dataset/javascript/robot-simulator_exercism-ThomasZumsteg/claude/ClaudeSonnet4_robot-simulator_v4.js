var Robot = function() {
  this.bearing = 'north';
  this.coordinates = [0, 0];
  this.directionIndex = 0;
}

var directions = ['north', 'east', 'south', 'west'];
var vectors = [[0, 1], [1, 0], [0, -1], [-1, 0]];
var directionMap = {
  'north': 0,
  'east': 1,
  'south': 2,
  'west': 3
};

var instructionMap = {
  'L': 'turnLeft',
  'R': 'turnRight',
  'A': 'advance'
};

Robot.prototype.orient = function(direction) {
  var index = directionMap[direction];
  if (index === undefined) {
    throw "Invalid Robot Bearing";
  }
  this.bearing = direction;
  this.directionIndex = index;
};

Robot.prototype.turnRight = function() {
  this.directionIndex = (this.directionIndex + 1) & 3;
  this.bearing = directions[this.directionIndex];
};

Robot.prototype.turnLeft = function() {
  this.directionIndex = (this.directionIndex + 3) & 3;
  this.bearing = directions[this.directionIndex];
};

Robot.prototype.at = function(x, y) {
  this.coordinates[0] = x;
  this.coordinates[1] = y;
};

Robot.prototype.advance = function() {
  var vector = vectors[this.directionIndex];
  this.coordinates[0] += vector[0];
  this.coordinates[1] += vector[1];
};

Robot.prototype.instructions = function(instruction_list) {
  var result = new Array(instruction_list.length);
  for (var i = 0; i < instruction_list.length; i++) {
    result[i] = instructionMap[instruction_list[i]];
  }
  return result;
};

Robot.prototype.place = function(args) {
  this.orient(args.direction);
  this.at(args.x, args.y);
};

Robot.prototype.evaluate = function(instruction_list) {
  for (var i = 0; i < instruction_list.length; i++) {
    var action = instructionMap[instruction_list[i]];
    this[action]();
  }
};

module.exports = Robot;
exports.directions = directions;