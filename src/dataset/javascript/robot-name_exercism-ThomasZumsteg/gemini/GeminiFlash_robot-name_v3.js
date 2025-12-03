var Robot = function() { this.name = getName() }

Robot.prototype.reset = function() {
	this.name = getName();
};

// Keeps track of robot names in use
var namesInUse = new Set();
const MAX_ROBOTS = 676000;

function getName() {
	let name;
	if (namesInUse.size >= MAX_ROBOTS) {
		throw new Error("All possible robot names have been generated.");
	}

	while (true) {
		let nameParts = [
			String.fromCharCode(Math.floor(Math.random() * 26) + 65),
			String.fromCharCode(Math.floor(Math.random() * 26) + 65),
			String.floor(Math.random() * 10),
			String.floor(Math.random() * 10),
			String.floor(Math.random() * 10)
		];
		name = nameParts.join('');

		if (!namesInUse.has(name)) {
			namesInUse.add(name);
			break;
		}
	}

	return name;
}

module.exports = Robot;