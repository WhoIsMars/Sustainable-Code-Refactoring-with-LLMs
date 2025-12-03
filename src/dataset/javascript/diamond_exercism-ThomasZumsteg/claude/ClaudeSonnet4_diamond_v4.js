class Diamond {
    makeDiamond(letter) {
        const n = letter.charCodeAt(0) - 65;
        const size = 2 * n + 1;
        const lines = new Array(size);
        
        for (let i = 0; i <= n; i++) {
            const char = String.fromCharCode(65 + i);
            const spaces = n - i;
            const middle = i === 0 ? '' : ' '.repeat(2 * i - 1);
            
            lines[i] = ' '.repeat(spaces) + char + middle + (i === 0 ? '' : char) + ' '.repeat(spaces);
            if (i > 0) {
                lines[size - 1 - i] = lines[i];
            }
        }
        
        return lines.join('\n') + '\n';
    }
}

module.exports = Diamond;