class CollatzConjecture {
    static steps(start: number): number {
        if (start <= 0 || !Number.isInteger(start)) {
            throw 'Only positive integers are allowed';
        }

        let count = 0;
        let n = start;

        while (n !== 1) {
            if ((n & 1) === 0) { // Check if n is even using bitwise AND
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
            count++;
        }

        return count;
    }
}

export default CollatzConjecture;