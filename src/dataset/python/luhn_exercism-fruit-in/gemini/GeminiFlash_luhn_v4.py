class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        self.checksum = 0

        if not (card_num.isdigit() and len(card_num) > 1):
            return

        digits = [int(d) for d in card_num[::-1]]
        for i in range(1, len(digits), 2):
            doubled_digit = digits[i] * 2
            digits[i] = doubled_digit - 9 if doubled_digit > 9 else doubled_digit

        self.checksum = sum(digits)

    def valid(self):
        return self.checksum % 10 == 0