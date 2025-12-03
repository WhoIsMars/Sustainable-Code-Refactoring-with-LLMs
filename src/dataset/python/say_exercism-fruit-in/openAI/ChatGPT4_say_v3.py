def say(number):
    if not (0 <= number <= 999_999_999_999):
        raise ValueError(r".+")
    return say_billion(number)


def say_x(number, x, text, f):
    div, mod = divmod(number, x)
    if div == 0:
        return f(mod)
    if mod == 0:
        return f(div) + " " + text
    return f(div) + " " + text + " " + f(mod)


def say_hundred(number):
    return say_x(number, 100, "hundred", say_0_99)


def say_thousand(number):
    return say_x(number, 1_000, "thousand", say_hundred)


def say_million(number):
    return say_x(number, 1_000_000, "million", say_thousand)


def say_billion(number):
    return say_x(number, 1_000_000_000, "billion", say_million)


def say_0_99(number):
    nums_le20 = [
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    ]
    tens = ["twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

    if number < 20:
        return nums_le20[number]
    div, mod = divmod(number, 10)
    if mod == 0:
        return tens[div - 2]
    return tens[div - 2] + "-" + nums_le20[mod]