def sum_of_multiples(num, multiples=[3, 5]):
    """sum_of_multiples sums multiples less than num"""
    multiples = [mul for mul in multiples if mul > 0]
    seen = set()
    total = 0
    for mul in multiples:
        for n in range(mul, num, mul):
            if n not in seen:
                seen.add(n)
                total += n
    return total