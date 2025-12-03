NUMBERS = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
TENS = ['', 'ten', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety']
TEENS = ['ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']
POWERS = ['', ' thousand', ' million', ' billion']

def say(num):
    """say constructs the english phrase for a number between 0 and one trillion"""
    if not (0 <= num < 1E12):
        raise AttributeError("Number must be between 0 and one trillion")
    if num == 0:
        return 'zero'

    parts = []
    p = 0
    while num > 0:
        num, power = divmod(num, 1000)
        if power > 0:
            str_pow = say_power(power) + POWERS[p]
            if p == 0 and 0 < power < 100 and num != 0:
                parts.append('and ' + str_pow)
            else:
                parts.append(str_pow)
        p += 1

    return ' '.join(reversed(parts))

def say_power(num):
    """say_power converts a number between 1 and 999 to the english phrase"""
    hundreds, remainder = divmod(num, 100)
    tens, ones = divmod(remainder, 10)
    parts = []

    if hundreds:
        parts.append(f"{NUMBERS[hundreds]} hundred")
        if remainder:
            parts.append("and")

    if tens == 1:
        parts.append(TEENS[ones])
    else:
        if tens:
            parts.append(TENS[tens])
        if ones:
            parts.append(NUMBERS[ones])

    return ' '.join(parts)