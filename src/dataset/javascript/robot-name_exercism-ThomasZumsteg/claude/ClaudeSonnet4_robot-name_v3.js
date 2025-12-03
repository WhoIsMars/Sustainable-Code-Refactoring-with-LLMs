var Robot = function() { this.name = getName() }

Robot.prototype.reset = function() {
	var oldName = this.name;
	namesInUse.delete(oldName);
	this.name = getName();
};

var namesInUse = new Set();
var availableNames = [];
var nameIndex = 0;

function generateAllNames() {
	var names = [];
	for (var i = 65; i <= 90; i++) {
		for (var j = 65; j <= 90; j++) {
			for (var k = 48; k <= 57; k++) {
				for (var l = 48; l <= 57; l++) {
					for (var m = 48; m <= 57; m++) {
						names.push(String.fromCharCode(i, j, k, l, m));
					}
				}
			}
		}
	}
	return names;
}

function shuffleArray(array) {
	for (var i = array.length - 1; i > 0; i--) {
		var j = Math.floor(Math.random() * (i + 1));
		var temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

function getName() {
	if (availableNames.length === 0) {
		availableNames = generateAllNames();
		shuffleArray(availableNames);
		nameIndex = 0;
	}
	
	if (nameIndex >= availableNames.length) {
		throw new Error('No more unique names available');
	}
	
	var name = availableNames[nameIndex++];
	namesInUse.add(name);
	return name;
}

module.exports = Robot;