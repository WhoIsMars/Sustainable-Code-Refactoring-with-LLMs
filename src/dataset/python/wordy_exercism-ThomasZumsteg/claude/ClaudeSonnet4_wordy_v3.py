"""Does a natrual language calculation"""
from operator import add, sub, mul, truediv
from re import compile as re_compile

OPERATORS = {
    "plus": add,
    "minus": sub,
    "multiplied by": mul,
    "divided by": truediv,
}

PATTERN = re_compile(
    r"What is (-?\d+)(?: (plus|minus|multiplied by|divided by) (-?\d+))*\?$"
)

def calculate(string):
    """Parses and preforms natrual language calculation"""
    match = PATTERN.match(string)
    if not match:
        raise ValueError
    
    parts = string[8:-1].split()  # Remove "What is " and "?"
    val = int(parts[0])
    
    i = 1
    while i < len(parts):
        if parts[i] == "multiplied" and i + 1 < len(parts) and parts[i + 1] == "by":
            operator = "multiplied by"
            num = int(parts[i + 2])
            i += 3
        elif parts[i] == "divided" and i + 1 < len(parts) and parts[i + 1] == "by":
            operator = "divided by"
            num = int(parts[i + 2])
            i += 3
        elif parts[i] in ("plus", "minus"):
            operator = parts[i]
            num = int(parts[i + 1])
            i += 2
        else:
            break
        
        val = OPERATORS[operator](val, num)
    
    return val