class Change {
    calculate(coins, value) {
        if (value < 0) throw new Error("Negative totals are not allowed.");
        
        coins = coins.filter(c => c <= value).sort((a, b) => b - a);
        const result = [];
        let remaining = value;

        for (const coin of coins) {
            while (remaining >= coin) {
                result.push(coin);
                remaining -= coin;
            }
            if (remaining === 0) break;
        }

        if (remaining !== 0) {
            throw new Error(`The total ${value} cannot be represented in the given currency.`);
        }

        return result.sort((a, b) => a - b);
    }
}

module.exports = Change;