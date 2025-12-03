var Robot = function() { this.name = getName() }

Robot.prototype.reset = function() {
	var oldName = this.name;
	namesInUse.delete(oldName);
	this.name = getName();
};

var namesInUse = new Set();
var availableNames = [];
var nameIndex = 0;

function initializeNames() {
	if (availableNames.length === 0) {
		for (var i = 65; i <= 90; i++) {
			for (var j = 65; j <= 90; j++) {
				for (var k = 48; k <= 57; k++) {
					for (var l = 48; l <= 57; l++) {
						for (var m = 48; m <= 57; m++) {
							availableNames.push(String.fromCharCode(i, j, k, l, m));
						}
					}
				}
			}
		}
		shuffleArray(availableNames);
	}
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
	initializeNames();
	
	if (nameIndex >= availableNames.length) {
		nameIndex = 0;
		shuffleArray(availableNames);
	}
	
	var name = availableNames[nameIndex++];
	namesInUse.add(name);
	return name;
}

module.exports = Robot;