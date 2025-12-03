def triplets_with_sum(number):
    return [
        [a, b, c]
        for a in range(1, number // 3)
        for b in range(a + 1, (number - a) // 2 + 1)
        if (c := number - a - b) > b and a * a + b * b == c * c
    ]