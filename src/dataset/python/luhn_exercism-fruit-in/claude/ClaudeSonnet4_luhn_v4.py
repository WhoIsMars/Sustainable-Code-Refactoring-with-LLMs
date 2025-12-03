class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        
        if not card_num.isdigit() or len(card_num) <= 1:
            self.checksum = 1
            return
        
        checksum = 0
        double = False
        
        for char in reversed(card_num):
            digit = int(char)
            if double:
                digit <<= 1
                if digit > 9:
                    digit -= 9
            checksum += digit
            double = not double
        
        self.checksum = checksum

    def valid(self):
        return self.checksum % 10 == 0