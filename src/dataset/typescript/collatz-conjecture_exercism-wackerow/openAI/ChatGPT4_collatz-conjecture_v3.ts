class CollatzConjecture {
    static steps(start: number): number {
        if (start <= 0 || !Number.isInteger(start)) throw 'Only positive numbers are allowed';
        let count = 0;
        while (start > 1) {
            start = (start & 1) === 0 ? start >> 1 : start * 3 + 1;
            count++;
        }
        return count;
    }
}

export default CollatzConjecture;