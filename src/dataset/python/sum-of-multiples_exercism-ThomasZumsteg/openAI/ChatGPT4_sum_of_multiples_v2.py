def sum_of_multiples(num, multiples=[3, 5]):
    """sum_of_multiples sums multiples less than num"""
    multiples = [mul for mul in multiples if mul != 0]
    lcm = lambda a, b: abs(a * b) // math.gcd(a, b)
    total = sum((num - 1) // mul * (mul + ((num - 1) // mul) * mul) // 2 for mul in multiples)
    overlap = sum((num - 1) // lcm(multiples[i], multiples[j]) * (lcm(multiples[i], multiples[j]) + ((num - 1) // lcm(multiples[i], multiples[j])) * lcm(multiples[i], multiples[j])) // 2
                  for i in range(len(multiples)) for j in range(i + 1, len(multiples)))
    return total - overlap