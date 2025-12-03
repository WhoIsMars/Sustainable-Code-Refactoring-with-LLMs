def steps(number):
    if number <= 0:
        raise ValueError(r".+")

    cache = {}

    def compute_steps(n):
        if n in cache:
            return cache[n]
        if n == 1:
            return 0
        if n % 2 == 0:
            result = 1 + compute_steps(n // 2)
        else:
            result = 1 + compute_steps(3 * n + 1)
        cache[n] = result
        return result

    return compute_steps(number)