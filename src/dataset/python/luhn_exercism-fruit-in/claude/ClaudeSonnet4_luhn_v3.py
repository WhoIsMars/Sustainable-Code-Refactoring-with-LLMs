class Luhn:
    def __init__(self, card_num):
        card_num = card_num.replace(' ', '')
        
        if not card_num.isdigit() or len(card_num) <= 1:
            self.checksum = 1
            return
        
        checksum = 0
        is_even_position = False
        
        for i in range(len(card_num) - 1, -1, -1):
            digit = int(card_num[i])
            
            if is_even_position:
                digit <<= 1
                if digit > 9:
                    digit -= 9
            
            checksum += digit
            is_even_position = not is_even_position
        
        self.checksum = checksum

    def valid(self):
        return self.checksum % 10 == 0