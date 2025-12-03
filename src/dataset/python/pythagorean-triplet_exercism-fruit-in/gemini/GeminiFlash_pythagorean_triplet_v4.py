def triplets_with_sum(number):
    triplets = []
    max_a = number // 3
    for a in range(1, max_a + 1):
        min_b = a + 1
        max_b = (number - a) // 2

        if min_b > max_b:
            continue

        for b in range(min_b, max_b + 1):
            c = number - a - b
            if a >= b or b >= c:
                continue

            if a * a + b * b == c * c:
                triplets.append([a, b, c])
    return triplets