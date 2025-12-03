NUMBERS = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
TENS = ['', 'ten', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety']
TEENS = ['ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen']
POWERS = ['', ' thousand', ' million', ' billion']

def say(num):
    if not (0 <= num < 1_000_000_000_000):
        raise AttributeError("Number must be between 0 and one trillion")
    if num == 0:
        return 'zero'

    parts = []
    for p, power_name in enumerate(POWERS):
        num, power = divmod(num, 1000)
        if power > 0:
            part = say_power(power) + power_name
            parts.append(part)
        if num == 0:
            break

    return ' '.join(reversed(parts)).replace(' and ', ' ', 1) if len(parts) > 1 else parts[0]

def say_power(num):
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

    return ' and '.join(parts) if hundreds and remainder else ' '.join(parts)