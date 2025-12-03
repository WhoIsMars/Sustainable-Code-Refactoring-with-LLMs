class Isogram {
    constructor(word) {
        this.word = word;
    }

    isIsogram() {
        const cleanedWord = this.word.toLowerCase().replace(/[-\s]/g, '');
        const letters = new Set();

        for (let i = 0; i < cleanedWord.length; i++) {
            const char = cleanedWord[i];
            if (letters.has(char)) {
                return false;
            }
            letters.add(char);
        }

        return true;
    }
}

module.exports = Isogram;