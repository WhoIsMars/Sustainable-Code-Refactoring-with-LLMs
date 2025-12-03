def say(number):
    if not 0 <= number <= 999_999_999_999:
        raise ValueError("Number must be between 0 and 999,999,999,999.")

    less_than_20 = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                     "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
                     "seventeen", "eighteen", "nineteen"]
    tens = ["twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

    def convert_0_to_999(n):
        if n < 20:
            return less_than_20[n]
        elif n < 100:
            return tens[n // 10 - 2] + ("-" + less_than_20[n % 10] if (n % 10) else "")
        else:
            return less_than_20[n // 100] + " hundred" + (" " + convert_0_to_999(n % 100) if (n % 100) else "")

    if number == 0:
        return "zero"

    parts = []
    billion = number // 1_000_000_000
    number %= 1_000_000_000
    million = number // 1_000_000
    number %= 1_000_000
    thousand = number // 1_000
    number %= 1_000

    if billion:
        parts.append(convert_0_to_999(billion) + " billion")
    if million:
        parts.append(convert_0_to_999(million) + " million")
    if thousand:
        parts.append(convert_0_to_999(thousand) + " thousand")
    if number:
        parts.append(convert_0_to_999(number))

    return " ".join(parts)