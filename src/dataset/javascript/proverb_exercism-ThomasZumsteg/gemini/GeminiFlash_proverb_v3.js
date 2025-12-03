class Proverb {
    constructor(...args) {
        this.words = [];
        this.qualifier = undefined;

        for (const arg of args) {
            if (typeof arg === 'string') {
                this.words.push(arg);
            } else if (typeof arg === 'object' && arg !== null && arg.qualifier !== undefined) {
                this.qualifier = arg.qualifier;
            }
        }
    }

    toString() {
        const result = [];
        const wordsLength = this.words.length;

        for (let i = 1; i < wordsLength; i++) {
            result.push(`For want of a ${this.words[i - 1]} the ${this.words[i]} was lost.`);
        }

        const lastWord = this.words[0];
        const qualifierPrefix = this.qualifier ? `${this.qualifier} ` : '';
        result.push(`And all for the want of a ${qualifierPrefix}${lastWord}.`);

        return result.join('\n');
    }
}

module.exports = Proverb;