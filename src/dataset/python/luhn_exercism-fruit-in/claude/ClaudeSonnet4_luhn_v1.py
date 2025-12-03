class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        self.checksum = 1

        if card_num.isdigit() and len(card_num) > 1:
            checksum = 0
            for i, digit in enumerate(reversed(card_num)):
                digit = int(digit)
                if i % 2 == 1:
                    digit *= 2
                    if digit > 9:
                        digit -= 9
                checksum += digit
            
            self.checksum = checksum

    def valid(self):
        return self.checksum % 10 == 0