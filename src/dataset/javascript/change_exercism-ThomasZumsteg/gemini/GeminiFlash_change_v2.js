class Change {
    calculate(coins, value) {
        if (value < 0) {
            throw new Error("Negative totals are not allowed.");
        }

        if (value === 0) {
            return [];
        }

        const sortedCoins = coins.sort((a, b) => b - a);
        let minChange = null;

        function findChange(remaining, currentChange, coinIndex) {
            if (remaining === 0) {
                const sortedCurrentChange = [...currentChange].sort((a, b) => a - b);
                if (!minChange || sortedCurrentChange.length < minChange.length) {
                    minChange = sortedCurrentChange;
                }
                return;
            }

            if (coinIndex >= sortedCoins.length || (minChange && currentChange.length >= minChange.length)) {
                return;
            }

            const coin = sortedCoins[coinIndex];

            if (coin <= remaining) {
                findChange(remaining - coin, [...currentChange, coin], coinIndex); // Use the same coin again
            }
            findChange(remaining, currentChange, coinIndex + 1); // Skip this coin
        }

        findChange(value, [], 0);

        if (!minChange) {
            throw new Error("The total " + value + " cannot be represented in the given currency.");
        }

        return minChange;
    }
}

module.exports = Change;