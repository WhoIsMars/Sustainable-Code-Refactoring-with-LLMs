Pangram = function(text) {
    this.text = text.toLowerCase();
}

Pangram.prototype.isPangram = function() {
    const seen = new Set();
    for (let i = 0; i < this.text.length; i++) {
        const charCode = this.text.charCodeAt(i);
        if (charCode >= 97 && charCode <= 122) { // a-z
            seen.add(this.text[i]);
        }
    }
    return seen.size === 26;
};

module.exports = Pangram