class Bowling {
    constructor() {
        this.rolls = [];
        this.frame = 0;
        this.extra = 0;
        this.rollCount = 0;
    }

    gameOver() {
        return this.frame >= 10 && this.extra <= 0;
    }

    roll(pins) {
        if (this.gameOver()) {
            throw new Error('Cannot roll after game is over');
        }

        if (pins < 0) {
            throw new Error('Negative roll is invalid');
        }

        const lastRoll = this.rolls.length > 0 ? this.rolls[this.rolls.length - 1] : 0;
        if (pins > 10 || (this.rollCount % 2 === 1 && lastRoll + pins > 10)) {
            throw new Error('Pin count exceeds pins on the lane');
        }

        if (this.frame === 9) {
            if (this.rollCount % 2 === 0 && pins === 10) {
                this.extra = 2;
            } else if (this.rollCount % 2 === 1 && lastRoll + pins === 10) {
                this.extra = 1;
            }
        } else if (this.frame > 9) {
            this.extra--;
        }

        this.rolls.push(pins);
        this.rollCount++;

        if (pins === 10) {
            this.frame++;
        } else if (this.rollCount % 2 === 0) {
            this.frame++;
        }
    }

    score() {
        if (!this.gameOver()) {
            throw new Error('Score cannot be taken until the end of the game');
        }

        let result = 0;
        let i = 0;
        for (let frame = 0; frame < 10; frame++) {
            const firstRoll = this.rolls[i];
            const secondRoll = this.rolls[i + 1];

            result += firstRoll + secondRoll;

            if (firstRoll === 10 || firstRoll + secondRoll === 10) {
                result += this.rolls[i + 2];
            }

            i += (firstRoll === 10 ? 1 : 2);
        }
        return result;
    }
}

module.exports = Bowling;