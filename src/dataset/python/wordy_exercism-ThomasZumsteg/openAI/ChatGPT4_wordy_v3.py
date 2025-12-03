"""Does a natural language calculation"""
from operator import add, sub, mul, truediv
import re

def calculate(string):
    """Parses and performs natural language calculation"""
    operators = {
        "plus": add,
        "minus": sub,
        "multiplied by": mul,
        "divided by": truediv,
    }
    pattern = re.compile(
        r"^What is (-?\d+)((?: (plus|minus|multiplied by|divided by) -?\d+)+)\?$"
    )
    match_obj = pattern.fullmatch(string)
    if not match_obj:
        raise ValueError("Invalid input format")
    
    val = int(match_obj.group(1))
    operations = match_obj.group(2).strip().split(" ")
    
    for i in range(0, len(operations), 2):
        func = operators[operations[i]]
        num = int(operations[i + 1])
        val = func(val, num)
    
    return val