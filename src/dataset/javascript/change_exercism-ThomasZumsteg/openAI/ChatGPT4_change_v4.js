class Change {
    calculate(coins, value) {
        if (value < 0) throw new Error("Negative totals are not allowed.");

        coins = coins.filter(c => c > 0).sort((a, b) => b - a);
        let min = null;

        const findChange = (remaining, change, index) => {
            if (remaining === 0) {
                if (!min || change.length < min.length) {
                    min = [...change];
                }
                return;
            }
            if (index >= coins.length || (min && change.length >= min.length)) return;

            const coin = coins[index];
            const maxCount = Math.floor(remaining / coin);

            for (let count = maxCount; count >= 0; count--) {
                findChange(remaining - count * coin, [...change, ...Array(count).fill(coin)], index + 1);
            }
        };

        findChange(value, [], 0);

        if (!min) throw new Error(`The total ${value} cannot be represented in the given currency.`);
        return min.sort((a, b) => a - b);
    }
}

module.exports = Change;