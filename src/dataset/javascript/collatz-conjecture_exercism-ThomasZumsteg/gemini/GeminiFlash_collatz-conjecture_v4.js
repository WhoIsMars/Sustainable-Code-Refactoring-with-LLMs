class CollatzConjecture {
    steps(num) {
        if (num <= 0) {
            throw new Error('Only positive numbers are allowed');
        }

        let stepsCount = 0;
        while (num > 1) {
            num = (num % 2 === 0) ? (num / 2) : (num * 3 + 1);
            stepsCount++;
        }

        return stepsCount;
    }
}

module.exports = CollatzConjecture;