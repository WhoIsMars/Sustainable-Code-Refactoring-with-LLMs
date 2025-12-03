def sum_of_multiples(num, multiples=[3, 5]):
    """sum_of_multiples sums multiples less than num"""
    multiples = [mul for mul in multiples if mul != 0]
    if not multiples:
        return 0
    lcm = lambda a, b: abs(a * b) // math.gcd(a, b)
    result = 0
    for i, mul in enumerate(multiples):
        result += (num - 1) // mul * (mul + ((num - 1) // mul) * mul) // 2
        for j in range(i):
            result -= (num - 1) // lcm(mul, multiples[j]) * (lcm(mul, multiples[j]) + ((num - 1) // lcm(mul, multiples[j])) * lcm(mul, multiples[j])) // 2
    return result