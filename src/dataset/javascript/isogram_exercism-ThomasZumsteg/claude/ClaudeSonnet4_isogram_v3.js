class Isogram {
    constructor(word) {
        this.word = word.toLowerCase();
    }

    isIsogram() {
        const seen = new Set();
        for (let i = 0; i < this.word.length; i++) {
            const char = this.word[i];
            if (char !== '-' && char !== ' ') {
                if (seen.has(char)) {
                    return false;
                }
                seen.add(char);
            }
        }
        return true;
    }
}

module.exports = Isogram;