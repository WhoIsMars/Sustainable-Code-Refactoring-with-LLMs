class Isogram {
    constructor(word) {
        this.word = word.toLowerCase();
        this._isIsogramCache = null;
    }

    isIsogram() {
        if (this._isIsogramCache !== null) {
            return this._isIsogramCache;
        }

        const seen = new Set();
        for (let i = 0; i < this.word.length; i++) {
            const char = this.word[i];
            if (char !== '-' && char !== ' ') {
                if (seen.has(char)) {
                    this._isIsogramCache = false;
                    return false;
                }
                seen.add(char);
            }
        }
        
        this._isIsogramCache = true;
        return true;
    }
}

module.exports = Isogram;