class Proverb {
    constructor() {
        const args = arguments;
        const words = [];
        let qualifier;
        
        for (let i = 0; i < args.length; i++) {
            const arg = args[i];
            if (typeof arg === 'string') {
                words.push(arg);
            } else if (typeof arg === 'object' && arg && !qualifier) {
                qualifier = arg.qualifier;
            }
        }
        
        this.words = words;
        this.qualifier = qualifier;
    }

    toString() {
        const words = this.words;
        const len = words.length;
        
        if (len === 0) return '';
        
        let result = '';
        
        for (let i = 1; i < len; i++) {
            result += 'For want of a ' + words[i-1] + ' the ' + words[i] + ' was lost.\n';
        }
        
        result += 'And all for the want of a ' + 
            (this.qualifier ? this.qualifier + ' ' : '') + words[0] + '.';
        
        return result;
    }
}

module.exports = Proverb;