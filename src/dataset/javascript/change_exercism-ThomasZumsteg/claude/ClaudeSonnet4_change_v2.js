class Change {
    calculate(coins, value) {
        if(value < 0)
            throw new Error("Negative totals are not allowed.");
        
        if(value === 0) return [];
        
        // Use dynamic programming approach for better efficiency
        const dp = new Array(value + 1).fill(null);
        dp[0] = [];
        
        const sortedCoins = coins.sort((a, b) => a - b);
        
        for(let amount = 1; amount <= value; amount++) {
            for(const coin of sortedCoins) {
                if(coin > amount) break;
                
                const remainder = amount - coin;
                if(dp[remainder] !== null) {
                    const candidate = [...dp[remainder], coin];
                    if(dp[amount] === null || candidate.length < dp[amount].length) {
                        dp[amount] = candidate;
                    }
                }
            }
        }
        
        if(dp[value] === null)
            throw new Error("The total " + value + " cannot be represented in the given currency.");
        
        return dp[value];
    }
}

module.exports = Change;