class Change {
    calculate(coins, value) {
        if (value < 0) throw new Error("Negative totals are not allowed.");

        coins = coins.filter(coin => coin > 0).sort((a, b) => b - a);
        let minChange = null;

        const findChange = (remaining, change, index) => {
            if (remaining === 0) {
                if (!minChange || change.length < minChange.length) {
                    minChange = [...change];
                }
                return;
            }
            if (index >= coins.length || (minChange && change.length >= minChange.length)) {
                return;
            }

            const coin = coins[index];
            const maxCount = Math.floor(remaining / coin);

            for (let count = maxCount; count >= 0; count--) {
                findChange(
                    remaining - count * coin,
                    [...change, ...Array(count).fill(coin)],
                    index + 1
                );
            }
        };

        findChange(value, [], 0);

        if (!minChange) {
            throw new Error(`The total ${value} cannot be represented in the given currency.`);
        }

        return minChange.sort((a, b) => a - b);
    }
}

module.exports = Change;