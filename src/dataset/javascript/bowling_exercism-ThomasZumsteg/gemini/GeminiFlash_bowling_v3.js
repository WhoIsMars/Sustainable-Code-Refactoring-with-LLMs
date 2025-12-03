class Bowling {
    constructor() {
        this.rolls = [];
        this.frame = 0;
        this.extraRolls = 0;
        this.rollInFrame = 0;
    }

    gameOver() {
        return this.frame >= 10 && this.extraRolls <= 0;
    }

    roll(pins) {
        if (this.gameOver()) {
            throw new Error('Cannot roll after game is over');
        }

        if (pins < 0) {
            throw new Error('Negative roll is invalid');
        }

        if (pins > 10 || (this.rollInFrame === 1 && this.rolls[this.rolls.length - 1] + pins > 10)) {
            throw new Error('Pin count exceeds pins on the lane');
        }

        if (this.frame === 9) {
            if (this.rollInFrame === 0 && pins === 10) {
                this.extraRolls = 2;
            } else if (this.rollInFrame === 1 && this.rolls[this.rolls.length - 1] + pins === 10) {
                this.extraRolls = 1;
            }
        } else if (this.frame > 9) {
            this.extraRolls--;
        }

        this.rolls.push(pins);

        if (pins === 10) {
            this.frame++;
            this.rollInFrame = 0;
        } else {
            this.rollInFrame++;
            if (this.rollInFrame === 2) {
                this.frame++;
                this.rollInFrame = 0;
            }
        }
    }

    score() {
        if (!this.gameOver()) {
            throw new Error('Score cannot be taken until the end of the game');
        }

        let score = 0;
        let rollIndex = 0;

        for (let frame = 0; frame < 10; frame++) {
            const firstRoll = this.rolls[rollIndex];
            const secondRoll = this.rolls[rollIndex + 1];

            score += firstRoll + secondRoll;

            if (firstRoll === 10 || firstRoll + secondRoll === 10) {
                score += this.rolls[rollIndex + 2];
            }

            rollIndex += (firstRoll === 10) ? 1 : 2;
        }

        return score;
    }
}

module.exports = Bowling;