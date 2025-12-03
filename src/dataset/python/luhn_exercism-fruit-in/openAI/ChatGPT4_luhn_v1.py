class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        self.checksum = 0

        if card_num.isdigit() and len(card_num) > 1:
            self.checksum = sum(
                int(d) if i % 2 == 0 else (2 * int(d) - 9 if 2 * int(d) > 9 else 2 * int(d))
                for i, d in enumerate(reversed(card_num))
            )

    def valid(self):
        return self.checksum % 10 == 0