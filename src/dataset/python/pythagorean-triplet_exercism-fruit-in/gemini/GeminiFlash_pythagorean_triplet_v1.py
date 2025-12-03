def triplets_with_sum(number):
    triplets = []
    for a in range(1, number // 3 + 1):
        a_squared = a * a
        for b in range(a + 1, (number - a) // 2 + 1):
            c = number - a - b
            if a < b < c:
                if a_squared + b * b == c * c:
                    triplets.append([a, b, c])
    return triplets