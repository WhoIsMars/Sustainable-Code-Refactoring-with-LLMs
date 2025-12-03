"""Does a natural language calculation"""
import re
from operator import add, sub, mul, truediv

def calculate(string):
    """Parses and performs natural language calculation"""
    operators = {
        "plus": add,
        "minus": sub,
        "multiplied by": mul,
        "divided by": truediv,
    }
    regex = r"What is (-?\d+)((?: (plus|minus|multiplied by|divided by) -?\d+)+)\?$"
    match_obj = re.fullmatch(regex, string)
    if not match_obj:
        raise ValueError("Invalid input format")
    
    val = int(match_obj.group(1))
    operations = re.findall(r"(plus|minus|multiplied by|divided by) (-?\d+)", match_obj.group(2))
    
    for op, num in operations:
        val = operators[op](val, int(num))
    return val