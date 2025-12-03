class Change {
    calculate(coins, value) {
        if (value < 0) throw new Error("Negative totals are not allowed.");

        coins = coins.filter(c => c <= value).sort((a, b) => b - a);
        let min = null;

        const findChange = (remaining, change, index) => {
            if (remaining === 0) {
                if (!min || change.length < min.length) {
                    min = [...change];
                }
                return;
            }
            for (let i = index; i < coins.length; i++) {
                if (coins[i] > remaining || (min && change.length >= min.length - 1)) continue;
                findChange(remaining - coins[i], [...change, coins[i]], i);
            }
        };

        findChange(value, [], 0);

        if (!min) throw new Error(`The total ${value} cannot be represented in the given currency.`);
        return min.sort((a, b) => a - b);
    }
}

module.exports = Change;