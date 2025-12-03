def roman(number):
    roman = []
    roman.append('M' * (number // 1000))
    number %= 1000
    roman.append('CM' if number >= 900 else 'D' * (number // 500))
    number %= 500
    roman.append('CD' if number >= 400 else 'C' * (number // 100))
    number %= 100
    roman.append('XC' if number >= 90 else 'L' * (number // 50))
    number %= 50
    roman.append('XL' if number >= 40 else 'X' * (number // 10))
    number %= 10
    roman.append('IX' if number == 9 else 'V' * (number // 5))
    number %= 5
    roman.append('IV' if number == 4 else 'I' * number)
    
    return ''.join(roman)