class CollatzConjecture {
    steps(num) {
        if (num <= 0) {
            throw new Error('Only positive numbers are allowed');
        }
        
        let steps = 0;
        
        while (num !== 1) {
            if (num & 1) {
                num = (num << 1) + num + 1;
            } else {
                num >>>= 1;
            }
            steps++;
        }
        
        return steps;
    }
}

module.exports = CollatzConjecture;