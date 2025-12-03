def sum_of_multiples(num, multiples=[3, 5]):
    """sum_of_multiples sums multiples less than num"""
    seen = set()
    total = 0
    for mul in multiples:
        if mul != 0:
            for i in range(mul, num, mul):
                if i not in seen:
                    total += i
                    seen.add(i)
    return total