var Robot = function() { this.name = getName() }

Robot.prototype.reset = function() {
	/* Give the robot a new name */
	namesInUse.delete(this.name);
	this.name = getName();
};

// Keeps track of robot names in use
var namesInUse = new Set();

// Pre-calculate character codes
var A_CODE = 65; // 'A'.charCodeAt(0)
var Z_CODE = 90; // 'Z'.charCodeAt(0)
var ZERO_CODE = 48; // '0'.charCodeAt(0)
var NINE_CODE = 57; // '9'.charCodeAt(0)

function getName() {
	/* Generates a robot name */
	// Inline optimized random functions
	var letter = function() { return Math.floor(Math.random() * 26) + A_CODE };
	var digit = function() { return Math.floor(Math.random() * 10) + ZERO_CODE };
	
	// Gets name that is not in use
	var name;
	do {
		name = String.fromCharCode(letter(), letter(), digit(), digit(), digit());
	} while( namesInUse.has(name) );

	namesInUse.add(name);
	return name;
}

module.exports = Robot;