class PerfectNumbers {
    classify(number) {
        if (number <= 0) {
            return "Classification is only possible for natural numbers.";
        }

        let factorSum = 1;
        for (let i = 2; i * i <= number; i++) {
            if (number % i === 0) {
                factorSum += i;
                if (i * i !== number) {
                    factorSum += number / i;
                }
            }
        }

        if (number < factorSum) {
            return "abundant";
        } else if (number > factorSum) {
            return "deficient";
        } else {
            return "perfect";
        }
    }
}

module.exports = PerfectNumbers;