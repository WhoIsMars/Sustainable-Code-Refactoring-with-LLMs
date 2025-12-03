Pangram = function(text) {
    this.text = text;
}

Pangram.prototype.isPangram = function() {
    const text = this.text.toLowerCase();
    if (text.length < 26) return false;

    const seen = new Set();
    for (let i = 0; i < text.length; i++) {
        const char = text[i];
        if (/[a-z]/.test(char)) {
            seen.add(char);
            if (seen.size === 26) return true;
        }
    }
    return false;
}

module.exports = Pangram