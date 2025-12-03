class Bowling {
    constructor() {
        this.rolls = [];
        this.currentFrame = 0;
        this.isSecondRoll = false;
        this.extraRolls = 0;
    }

    gameOver() { 
        return this.currentFrame >= 10 && this.extraRolls <= 0; 
    }

    roll(pins) {
        if (this.gameOver()) {
            throw new Error('Cannot roll after game is over');
        }
        if (pins < 0) {
            throw new Error('Negative roll is invalid');
        }
        if (pins > 10 || (this.isSecondRoll && this.rolls[this.rolls.length - 1] + pins > 10)) {
            throw new Error('Pin count exceeds pins on the lane');
        }

        if (this.currentFrame === 9) {
            if (!this.isSecondRoll && pins === 10) {
                this.extraRolls = 2;
            } else if (this.isSecondRoll && pins + this.rolls[this.rolls.length - 1] === 10) {
                this.extraRolls = 1;
            }
        } else if (this.currentFrame > 9) {
            this.extraRolls--;
        }

        if (pins === 10) {
            this.currentFrame++;
            this.isSecondRoll = false;
        } else {
            if (this.isSecondRoll) this.currentFrame++;
            this.isSecondRoll = !this.isSecondRoll;
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