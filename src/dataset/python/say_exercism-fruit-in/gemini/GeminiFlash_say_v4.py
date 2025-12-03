def say(number):
    if not 0 <= number <= 999_999_999_999:
        raise ValueError(".+")

    less_than_20 = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                     "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                     "eighteen", "nineteen"]
    tens = ["twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]
    scales = ["thousand", "million", "billion"]

    def _say_0_99(n):
        if n < 20:
            return less_than_20[n]
        elif n < 100:
            ten, rem = divmod(n, 10)
            return tens[ten - 2] + ("-" + less_than_20[rem] if rem else "")
        return ""

    def _say_0_999(n):
        hundred, rem = divmod(n, 100)
        if hundred == 0:
            return _say_0_99(rem)
        else:
            return less_than_20[hundred] + " hundred" + (" " + _say_0_99(rem) if rem else "")

    if number == 0:
        return "zero"

    chunks = []
    for scale in scales:
        number, rem = divmod(number, 1000)
        if rem != 0:
            chunks.append(_say_0_999(rem) + " " + scale)

    if number != 0:
        chunks.append(_say_0_999(number) + " billion")

    return " ".join(chunks[::-1]).strip()