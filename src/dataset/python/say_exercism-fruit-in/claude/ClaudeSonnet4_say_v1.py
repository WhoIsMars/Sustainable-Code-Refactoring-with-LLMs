def say(number):
    if number < 0 or number > 999_999_999_999:
        raise ValueError(r".+")

    return say_billion(number)


def say_x(number, x, text, f):
    if number < x:
        return f(number)
    quotient, remainder = divmod(number, x)
    if remainder == 0:
        return f(quotient) + " " + text
    else:
        return f(quotient) + " " + text + " " + f(remainder)


def say_hundred(number):
    return say_x(number, 100, "hundred", say_0_99)


def say_thousand(number):
    return say_x(number, 1_000, "thousand", say_hundred)


def say_million(number):
    return say_x(number, 1_000_000, "million", say_thousand)


def say_billion(number):
    return say_x(number, 1_000_000_000, "billion", say_million)


# Pre-computed lookup tables moved to module level to avoid recreation
_NUMS_LE20 = ("zero", "one", "two", "three", "four",
              "five", "six", "seven", "eight", "nine",
              "ten", "eleven", "twelve", "thirteen", "fourteen",
              "fifteen", "sixteen", "seventeen", "eighteen", "nineteen")

_TENS = ("twenty", "thirty", "forty", "fifty",
         "sixty", "seventy", "eighty", "ninety")


def say_0_99(number):
    if number < 20:
        return _NUMS_LE20[number]
    elif number % 10 == 0:
        return _TENS[number // 10 - 2]
    else:
        return _TENS[number // 10 - 2] + "-" + _NUMS_LE20[number % 10]