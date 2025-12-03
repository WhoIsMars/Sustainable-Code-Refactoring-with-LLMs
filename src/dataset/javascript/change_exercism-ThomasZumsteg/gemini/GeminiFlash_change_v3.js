class Change {
    calculate(coins, value) {
        if (value < 0) {
            throw new Error("Negative totals are not allowed.");
        }

        const sortedCoins = [...coins].sort((a, b) => b - a);
        let minChange = null;

        const findChange = (currentChange, remaining, coinIndex) => {
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
                findChange([...currentChange, coin], remaining - coin, coinIndex);
            }

            findChange(currentChange, remaining, coinIndex + 1);
        };

        findChange([], value, 0);

        if (!minChange) {
            throw new Error("The total " + value + " cannot be represented in the given currency.");
        }

        return minChange;
    }
}

module.exports = Change;