class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        self.checksum = 0

        if not (card_num.isdigit() and len(card_num) > 1):
            return

        digits_sum = 0
        for i, digit in enumerate(reversed(card_num)):
            digit = int(digit)
            if i % 2 != 0:
                digit *= 2
                if digit > 9:
                    digit -= 9
            digits_sum += digit

        self.checksum = digits_sum

    def valid(self):
        return self.checksum % 10 == 0