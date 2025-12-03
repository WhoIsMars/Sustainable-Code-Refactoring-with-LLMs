class Change {
    calculate(coins, value) {
        if(value < 0)
            throw new Error("Negative totals are not allowed.");
        
        if(value === 0) return [];
        
        const sortedCoins = coins.sort((a, b) => b - a);
        const memo = new Map();
        
        const findMinChange = (remaining) => {
            if(remaining === 0) return [];
            if(remaining < 0) return null;
            if(memo.has(remaining)) return memo.get(remaining);
            
            let minChange = null;
            
            for(const coin of sortedCoins) {
                if(coin > remaining) continue;
                
                const subResult = findMinChange(remaining - coin);
                if(subResult !== null) {
                    const currentChange = [coin, ...subResult];
                    if(minChange === null || currentChange.length < minChange.length) {
                        minChange = currentChange;
                    }
                }
            }
            
            memo.set(remaining, minChange);
            return minChange;
        };
        
        const result = findMinChange(value);
        if(result === null)
            throw new Error("The total " + value + " cannot be represented in the given currency.");
        
        return result.sort((a, b) => a - b);
    }
}

module.exports = Change;