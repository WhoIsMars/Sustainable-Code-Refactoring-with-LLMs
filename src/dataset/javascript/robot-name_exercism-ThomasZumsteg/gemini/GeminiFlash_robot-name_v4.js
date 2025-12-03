var Robot = function() { this.name = getName() }

Robot.prototype.reset = function() {
	this.name = getName();
};

// Keeps track of robot names in use
var namesInUse = new Set();
const MAX_ROBOTS = 676000;

function getName() {
	/* Generates a robot name */
	if (namesInUse.size >= MAX_ROBOTS) {
        throw new Error("All possible robot names have been generated.");
    }

	const letterChars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
    const digitChars = '0123456789';

	let name;
	do {
		name = letterChars[Math.floor(Math.random() * 26)] +
               letterChars[Math.floor(Math.random() * 26)] +
               digitChars[Math.floor(Math.random() * 10)] +
               digitChars[Math.floor(Math.random() * 10)] +
               digitChars[Math.floor(Math.random() * 10)];
	} while( namesInUse.has(name) );

	namesInUse.add(name);
	return name;
}

module.exports = Robot;