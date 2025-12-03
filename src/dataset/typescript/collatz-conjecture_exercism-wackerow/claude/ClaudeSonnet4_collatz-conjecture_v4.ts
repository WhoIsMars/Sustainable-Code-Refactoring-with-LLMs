class CollatzConjecture {
    private static cache = new Map<number, number>();
    
    static steps(start: number): number {
        if (start <= 0 || start % 1 !== 0) {throw 'Only positive numbers are allowed'}
        
        if (this.cache.has(start)) {
            return this.cache.get(start)!;
        }
        
        let count = 0;
        let current = start;
        const path: number[] = [];
        
        while (current > 1 && !this.cache.has(current)) {
            path.push(current);
            current = (current & 1) === 0 ? current >>> 1 : (3 * current) + 1;
            count++;
        }
        
        if (current > 1) {
            count += this.cache.get(current)!;
        }
        
        for (let i = path.length - 1; i >= 0; i--) {
            this.cache.set(path[i], count - i);
        }
        
        return count;
    }
}

export default CollatzConjecture