class Robot {
    constructor() {
        this.name = Robot.getName();
    }

    reset() {
        Robot.releaseName(this.name);
        this.name = Robot.getName();
    }

    static getName() {
        if (!Robot.availableNames) {
            Robot.generateNames();
        }
        const name = Robot.availableNames.pop();
        Robot.namesInUse.add(name);
        return name;
    }

    static releaseName(name) {
        if (Robot.namesInUse.has(name)) {
            Robot.namesInUse.delete(name);
            Robot.availableNames.push(name);
        }
    }

    static generateNames() {
        Robot.availableNames = [];
        for (let i = 0; i < 26; i++) {
            for (let j = 0; j < 26; j++) {
                for (let k = 0; k < 1000; k++) {
                    const name = String.fromCharCode(65 + i, 65 + j) + k.toString().padStart(3, '0');
                    Robot.availableNames.push(name);
                }
            }
        }
        Robot.shuffleArray(Robot.availableNames);
        Robot.namesInUse = new Set();
    }

    static shuffleArray(array) {
        for (let i = array.length - 1; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
            [array[i], array[j]] = [array[j], array[i]];
        }
    }
}

module.exports = Robot;