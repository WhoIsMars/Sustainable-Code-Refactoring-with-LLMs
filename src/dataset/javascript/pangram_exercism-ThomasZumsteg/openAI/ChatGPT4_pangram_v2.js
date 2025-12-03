Pangram = function(text) {
    this.text = text.toLowerCase();
}

Pangram.prototype.isPangram = function() {
    const seen = new Set();
    for (const char of this.text) {
        if (char >= 'a' && char <= 'z') {
            seen.add(char);
            if (seen.size === 26) return true;
        }
    }
    return false;
}

module.exports = Pangram;