Pangram = function(text) {
    this.text = text;
}

Pangram.prototype.isPangram = function() {
    const seen = new Set();
    const text = this.text.toLowerCase();
    
    for (let i = 0; i < text.length; i++) {
        const char = text[i];
        if (char >= 'a' && char <= 'z') {
            seen.add(char);
            if (seen.size === 26) {
                return true;
            }
        }
    }
    
    return seen.size === 26;
}

module.exports = Pangram