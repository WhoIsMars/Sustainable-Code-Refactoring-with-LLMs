Pangram = function(text) {
    this.text = text;
};

Pangram.prototype.isPangram = function() {
    const text = this.text.toLowerCase();
    const alphabet = 'abcdefghijklmnopqrstuvwxyz';
    for (let i = 0; i < alphabet.length; i++) {
        if (!text.includes(alphabet[i])) {
            return false;
        }
    }
    return true;
};

module.exports = Pangram;