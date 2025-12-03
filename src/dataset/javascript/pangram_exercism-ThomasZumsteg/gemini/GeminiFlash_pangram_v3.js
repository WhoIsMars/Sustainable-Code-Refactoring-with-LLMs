Pangram = function(text) {
    this.text = text;
}

Pangram.prototype.isPangram = function() {
    const text = this.text.toLowerCase();
    const seen = new Set();

    for (let i = 0; i < text.length; i++) {
        const char = text[i];
        if (/[a-z]/.test(char)) {
            seen.add(char);
        }
    }

    return seen.size === 26;
}

module.exports = Pangram