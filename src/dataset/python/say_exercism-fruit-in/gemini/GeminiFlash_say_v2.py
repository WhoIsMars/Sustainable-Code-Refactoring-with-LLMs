def say(number):
    if not 0 <= number <= 999_999_999_999:
        raise ValueError("Number must be between 0 and 999,999,999,999.")

    less_than_20 = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                    "eighteen", "nineteen"]
    tens = ["twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

    def _say_0_to_99(n):
        if n < 20:
            return less_than_20[n]
        else:
            ten, remainder = divmod(n, 10)
            return tens[ten - 2] + ("-" + less_than_20[remainder] if remainder else "")

    def _say_0_to_999(n):
        hundred, remainder = divmod(n, 100)
        if hundred == 0:
            return _say_0_to_99(remainder)
        else:
            return less_than_20[hundred] + " hundred" + (" " + _say_0_to_99(remainder) if remainder else "")

    if number == 0:
        return "zero"

    chunks = []
    billion, number = divmod(number, 1_000_000_000)
    if billion:
        chunks.append(_say_0_to_999(billion) + " billion")

    million, number = divmod(number, 1_000_000)
    if million:
        chunks.append(_say_0_to_999(million) + " million")

    thousand, number = divmod(number, 1_000)
    if thousand:
        chunks.append(_say_0_to_999(thousand) + " thousand")

    if number:
        chunks.append(_say_0_to_999(number))

    return " ".join(chunks)