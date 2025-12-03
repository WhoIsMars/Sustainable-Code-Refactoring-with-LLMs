class Proverb {
    constructor() {
        const args = Array.from(arguments);
        this.words = args.filter(arg => typeof arg === 'string');
        const options = args.find(arg => typeof arg === 'object');
        this.qualifier = options?.qualifier;
    }

    toString() {
        if (this.words.length === 0) return '';
        
        const lines = [];
        
        for (let i = 1; i < this.words.length; i++) {
            lines.push(`For want of a ${this.words[i-1]} the ${this.words[i]} was lost.`);
        }
        
        const qualifierPrefix = this.qualifier ? `${this.qualifier} ` : '';
        lines.push(`And all for the want of a ${qualifierPrefix}${this.words[0]}.`);
        
        return lines.join('\n');
    }
}

module.exports = Proverb;