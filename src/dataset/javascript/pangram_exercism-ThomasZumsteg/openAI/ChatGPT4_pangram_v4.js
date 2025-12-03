Pangram = function(text) {
    this.text = text.toLowerCase();
}

Pangram.prototype.alphabetSet = new Set("abcdefghijklmnopqrstuvwxyz");

Pangram.prototype.isPangram = function() {
    const textSet = new Set(this.text);
    for (const letter of Pangram.prototype.alphabetSet) {
        if (!textSet.has(letter)) return false;
    }
    return true;
}

module.exports = Pangram;