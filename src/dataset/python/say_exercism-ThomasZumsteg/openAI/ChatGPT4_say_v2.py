NUMBERS = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
TENS = ['', '', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety']
TEENS = ['ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']
POWERS = ['', ' thousand', ' million', ' billion']

def say(num):
    """say constructs the english phrase for a number between 0 and one trillion"""
    if not (0 <= num < 1E12):
        raise ValueError("Number must be between 0 and one trillion")
    if num == 0:
        return 'zero'

    parts = []
    for p, power in enumerate(iter_powers(num)):
        if power > 0:
            parts.append(say_power(power) + POWERS[p])
    return ' '.join(reversed(parts)).strip()

def iter_powers(num):
    """Generator to yield powers of 1000 from the number."""
    while num > 0:
        num, power = divmod(num, 1000)
        yield power

def say_power(num):
    """say_power converts a number between 1 and 999 to the english phrase"""
    hundreds, remainder = divmod(num, 100)
    tens, ones = divmod(remainder, 10)
    parts = []

    if hundreds:
        parts.append(f"{NUMBERS[hundreds]} hundred")
    if tens == 1:
        parts.append(TEENS[ones])
    else:
        if tens:
            parts.append(TENS[tens])
        if ones:
            parts.append(NUMBERS[ones])

    return ' '.join(parts)