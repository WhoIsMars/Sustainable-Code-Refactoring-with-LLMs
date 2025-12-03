class Robot {
    constructor() {
        this.name = generateUniqueName();
    }

    reset() {
        namesInUse.delete(this.name);
        this.name = generateUniqueName();
    }
}

const namesInUse = new Set();

function generateUniqueName() {
    let name;
    do {
        name = generateName();
    } while (namesInUse.has(name));
    namesInUse.add(name);
    return name;
}

function generateName() {
    const letters = String.fromCharCode(
        65 + Math.floor(Math.random() * 26),
        65 + Math.floor(Math.random() * 26)
    );
    const digits = String(Math.floor(100 + Math.random() * 900));
    return letters + digits;
}

module.exports = Robot;