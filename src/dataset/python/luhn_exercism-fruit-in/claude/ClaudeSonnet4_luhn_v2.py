class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        self.checksum = 1

        if card_num.isdigit() and len(card_num) > 1:
            checksum = 0
            for i, digit in enumerate(reversed(card_num)):
                d = int(digit)
                if i % 2 == 1:
                    d *= 2
                    if d > 9:
                        d -= 9
                checksum += d
            self.checksum = checksum

    def valid(self):
        return self.checksum % 10 == 0