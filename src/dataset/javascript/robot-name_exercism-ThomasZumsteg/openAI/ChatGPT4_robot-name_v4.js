const Robot = function() {
    this.name = generateUniqueName();
};

Robot.prototype.reset = function() {
    namesInUse.delete(this.name);
    this.name = generateUniqueName();
};

const namesInUse = new Set();
const CHAR_CODE_A = 'A'.charCodeAt(0);
const CHAR_CODE_Z = 'Z'.charCodeAt(0);
const CHAR_CODE_0 = '0'.charCodeAt(0);
const CHAR_CODE_9 = '9'.charCodeAt(0);

function generateRandomChar(start, end) {
    return String.fromCharCode(Math.floor(Math.random() * (end - start + 1)) + start);
}

function generateName() {
    return (
        generateRandomChar(CHAR_CODE_A, CHAR_CODE_Z) +
        generateRandomChar(CHAR_CODE_A, CHAR_CODE_Z) +
        generateRandomChar(CHAR_CODE_0, CHAR_CODE_9) +
        generateRandomChar(CHAR_CODE_0, CHAR_CODE_9) +
        generateRandomChar(CHAR_CODE_0, CHAR_CODE_9)
    );
}

function generateUniqueName() {
    let name;
    do {
        name = generateName();
    } while (namesInUse.has(name));
    namesInUse.add(name);
    return name;
}

module.exports = Robot;