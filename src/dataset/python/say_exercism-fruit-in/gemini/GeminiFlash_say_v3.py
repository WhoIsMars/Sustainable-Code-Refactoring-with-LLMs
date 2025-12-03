def say(number):
    if not 0 <= number <= 999_999_999_999:
        raise ValueError(r".+")

    less_than_20 = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                     "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                     "eighteen", "nineteen"]
    tens = ["twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

    def say_0_99(n):
        if n < 20:
            return less_than_20[n]
        return tens[n // 10 - 2] + ("-" + less_than_20[n % 10] if (n % 10) else "")

    def say_0_999(n):
        if n < 100:
            return say_0_99(n)
        return less_than_20[n // 100] + " hundred" + (" " + say_0_99(n % 100) if (n % 100) else "")

    def say_0_999_999(n):
        if n < 1000:
            return say_0_999(n)
        return say_0_999(n // 1000) + " thousand" + (" " + say_0_999(n % 1000) if (n % 1000) else "")

    def say_0_999_999_999(n):
        if n < 1_000_000:
            return say_0_999_999(n)
        return say_0_999(n // 1_000_000) + " million" + (" " + say_0_999_999(n % 1_000_000) if (n % 1_000_000) else "")

    if number < 1_000_000_000:
        return say_0_999_999_999(number)
    return say_0_999(number // 1_000_000_000) + " billion" + (" " + say_0_999_999_999(number % 1_000_000_000) if (number % 1_000_000_000) else "")


def say_x(number, x, text, f):
    if number < x:
        return f(number)
    elif number % x == 0:
        return f(number // x) + " " + text
    else:
        return f(number // x) + " " + text + " " + f(number % x)


def say_hundred(number):
    return say_x(number, 100, "hundred", say_0_99)


def say_thousand(number):
    return say_x(number, 1_000, "thousand", say_hundred)


def say_million(number):
    return say_x(number, 1_000_000, "million", say_thousand)


def say_billion(number):
    return say_x(number, 1_000_000_000, "billion", say_million)


def say_0_99(number):
    nums_le20 = ["zero", "one", "two", "three", "four",
                 "five", "six", "seven", "eight", "nine",
                 "ten", "eleven", "twelve", "thirteen", "fourteen",
                 "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", ]
    tens = ["twenty", "thirty", "forty", "fifty",
            "sixty", "seventy", "eighty", "ninety"]

    if number < 20:
        return nums_le20[number]
    elif number % 10 == 0:
        return tens[number // 10 - 2]
    else:
        return say_0_99(number // 10 * 10) + "-" + say_0_99(number % 10)