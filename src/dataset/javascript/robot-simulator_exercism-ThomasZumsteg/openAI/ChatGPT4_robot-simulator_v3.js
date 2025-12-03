class Robot {
    constructor() {
        this.bearing = null;
        this.coordinates = [0, 0];
    }

    static directions = ['north', 'east', 'south', 'west'];
    static vectors = { north: [0, 1], east: [1, 0], south: [0, -1], west: [-1, 0] };
    static instructionsMap = { L: 'turnLeft', R: 'turnRight', A: 'advance' };

    orient(direction) {
        if (!Robot.directions.includes(direction)) throw "Invalid Robot Bearing";
        this.bearing = direction;
    }

    turnRight() {
        this.bearing = Robot.directions[(Robot.directions.indexOf(this.bearing) + 1) % 4];
    }

    turnLeft() {
        this.bearing = Robot.directions[(Robot.directions.indexOf(this.bearing) + 3) % 4];
    }

    at(x, y) {
        this.coordinates = [x, y];
    }

    advance() {
        const [dx, dy] = Robot.vectors[this.bearing];
        this.coordinates[0] += dx;
        this.coordinates[1] += dy;
    }

    instructions(instructionList) {
        return [...instructionList].map(instruction => Robot.instructionsMap[instruction]);
    }

    place({ direction, x, y }) {
        this.orient(direction);
        this.at(x, y);
    }

    evaluate(instructionList) {
        this.instructions(instructionList).forEach(action => this[action]());
    }
}

module.exports = Robot;
exports.directions = Robot.directions;