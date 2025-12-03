var Robot = function() { this.name = getName() }

Robot.prototype.reset = function() {
	this.name = getName();
};

// Keeps track of robot names in use
var namesInUse = new Set();
const MAX_ROBOTS = 676000; // Maximum possible robot names

function getName() {
	/* Generates a robot name */
	if (namesInUse.size >= MAX_ROBOTS) {
        throw new Error("All possible robot names have been used.");
    }

	let name;
	do {
		name = generateName();
	} while (namesInUse.has(name));

	namesInUse.add(name);
	return name;
}

function generateName() {
    let result = '';
    for (let i = 0; i < 2; i++) {
        result += String.fromCharCode(Math.floor(Math.random() * 26) + 65); // A-Z
    }
    for (let i = 0; i < 3; i++) {
        result += String.fromCharCode(Math.floor(Math.random() * 10) + 48); // 0-9
    }
    return result;
}

module.exports = Robot;