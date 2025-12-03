class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        self.checksum = 0

        if card_num.isdigit() and len(card_num) > 1:
            digits = [int(d) for d in card_num]
            total = 0
            for i in range(len(digits) - 2, -1, -2):
                digit = int(digits[i]) * 2
                total += digit - 9 if digit > 9 else digit
            for i in range(len(digits) - 1, -1, -2):
                total += int(digits[i])
            self.checksum = total

    def valid(self):
        return self.checksum % 10 == 0