class Isogram {
    constructor(word) {
        this.word = word.toLowerCase().replace(/[-\s]/g, '');
    }

    isIsogram() {
        const seen = new Set();
        for (const char of this.word) {
            if (seen.has(char)) return false;
            seen.add(char);
        }
        return true;
    }
}

module.exports = Isogram;