def sum_of_multiples(num, multiples=[3, 5]):
    """sum_of_multiples sums multiples less than num"""
    seen = set()
    total = 0
    for mul in multiples:
        if mul != 0:
            start = mul
            while start < num:
                if start not in seen:
                    total += start
                    seen.add(start)
                start += mul
    return total