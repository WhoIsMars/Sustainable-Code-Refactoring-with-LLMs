class Bowling {
    constructor() {
        this.rolls = [];
        this.frame = 0;
        this.extra = 0;
        this.second = false;
    }

    gameOver() {
        return this.frame >= 10 && this.extra <= 0;
    }

    roll(pins) {
        if (this.gameOver()) {
            throw new Error('Cannot roll after game is over');
        }
        if (pins < 0 || pins > 10 || (this.second && this.rolls[this.rolls.length - 1] + pins > 10)) {
            throw new Error('Invalid pin count');
        }

        if (this.frame === 9) {
            if (!this.second && pins === 10) {
                this.extra = 2;
            } else if (this.second && this.rolls[this.rolls.length - 1] + pins === 10) {
                this.extra = 1;
            }
        } else if (this.frame > 9) {
            this.extra--;
        }

        if (pins === 10 && !this.second) {
            this.frame++;
        } else {
            this.frame += this.second ? 1 : 0;
            this.second = !this.second;
        }

        this.rolls.push(pins);
    }

    score() {
        if (!this.gameOver()) {
            throw new Error('Score cannot be taken until the end of the game');
        }

        let result = 0;
        let i = 0;

        for (let frame = 0; frame < 10; frame++) {
            const frameScore = this.rolls[i] + (this.rolls[i + 1] || 0);

            if (this.rolls[i] === 10) { // Strike
                result += frameScore + (this.rolls[i + 2] || 0);
                i++;
            } else if (frameScore === 10) { // Spare
                result += frameScore + (this.rolls[i + 2] || 0);
                i += 2;
            } else {
                result += frameScore;
                i += 2;
            }
        }

        return result;
    }
}

module.exports = Bowling;