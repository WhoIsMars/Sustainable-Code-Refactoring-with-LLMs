class Proverb {
    constructor(...args) {
        this.words = [];
        this.qualifier = null;
        
        for (let i = 0; i < args.length; i++) {
            const arg = args[i];
            if (typeof arg === 'string') {
                this.words.push(arg);
            } else if (typeof arg === 'object' && arg && arg.qualifier) {
                this.qualifier = arg.qualifier;
            }
        }
    }

    toString() {
        const wordsLength = this.words.length;
        if (wordsLength === 0) return '';
        
        const result = new Array(wordsLength);
        
        for (let i = 1; i < wordsLength; i++) {
            result[i - 1] = `For want of a ${this.words[i - 1]} the ${this.words[i]} was lost.`;
        }
        
        result[wordsLength - 1] = `And all for the want of a ${this.qualifier ? this.qualifier + ' ' : ''}${this.words[0]}.`;
        
        return result.join('\n');
    }
}

module.exports = Proverb;