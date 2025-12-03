class CollatzConjecture {
    private static cache = new Map<number, number>();
    
    static steps(start: number): number {
        if (start <= 0 || !Number.isInteger(start)) {
            throw 'Only positive numbers are allowed';
        }
        
        if (this.cache.has(start)) {
            return this.cache.get(start)!;
        }
        
        const originalStart = start;
        let count = 0;
        const path: number[] = [];
        
        while (start > 1 && !this.cache.has(start)) {
            path.push(start);
            start = (start & 1) === 0 ? start >>> 1 : start * 3 + 1;
            count++;
        }
        
        const baseSteps = start > 1 ? this.cache.get(start)! : 0;
        
        for (let i = path.length - 1; i >= 0; i--) {
            count = baseSteps + (path.length - i);
            this.cache.set(path[i], count);
        }
        
        return this.cache.get(originalStart)!;
    }
}

export default CollatzConjecture;