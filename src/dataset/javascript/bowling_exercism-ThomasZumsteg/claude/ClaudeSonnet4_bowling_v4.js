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
        if (pins < 0) {
            throw new Error('Negative roll is invalid');
        }
        if (pins > 10 || (this.second && this.rolls[this.rolls.length - 1] + pins > 10)) {
            throw new Error('Pin count exceeds pins on the lane');
        }

        if (this.frame === 9) {
            if (!this.second && pins === 10) {
                this.extra = 2;
            } else if (this.second && pins + this.rolls[this.rolls.length - 1] === 10) {
                this.extra = 1;
            }
        } else if (this.frame > 9) {
            this.extra--; 
        }

        if (pins === 10) {
            this.frame++;
            this.second = false;
        } else {
            if (this.second) this.frame++;
            this.second = !this.second;
        }
        this.rolls.push(pins);
    }

    score() {
        if (!this.gameOver()) {
            throw new Error('Score cannot be taken until the end of the game');
        }
        
        let result = 0;
        let rollIndex = 0;
        
        for (let frame = 0; frame < 10; frame++) {
            const firstRoll = this.rolls[rollIndex];
            const secondRoll = this.rolls[rollIndex + 1];
            
            result += firstRoll + secondRoll;
            
            if (firstRoll === 10 || firstRoll + secondRoll === 10) {
                result += this.rolls[rollIndex + 2];
            }
            
            rollIndex += firstRoll === 10 ? 1 : 2;
        }
        
        return result;
    }
}

module.exports = Bowling;