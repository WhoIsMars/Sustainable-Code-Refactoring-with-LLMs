Pangram = function(text) {
    this.text = text.toLowerCase();
}

Pangram.prototype.alphabet = "abcdefghijklmnopqrstuvwxyz";

Pangram.prototype.isPangram = function() {
    const seen = new Set();
    for (const char of this.text) {
        if (this.alphabet.includes(char)) {
            seen.add(char);
            if (seen.size === 26) return true;
        }
    }
    return false;
}

module.exports = Pangram;