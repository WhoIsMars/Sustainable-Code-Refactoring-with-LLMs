"""Does a natrual language calculation"""
from operator import add, sub, mul, truediv
from re import compile as re_compile

def calculate(string):
    """Parses and preforms natrual language calculation"""
    operators = {"plus": add, "minus": sub, "multiplied by": mul, "divided by": truediv}
    
    pattern = re_compile(r"What is (-?\d+)((?:\s(?:plus|minus|multiplied by|divided by)\s-?\d+)+)\?$")
    regex_match = pattern.match(string)
    
    if not regex_match:
        raise ValueError
    
    val = int(regex_match.group(1))
    remaining = regex_match.group(2)
    
    step_pattern = re_compile(r"\s(plus|minus|multiplied by|divided by)\s(-?\d+)")
    for step in step_pattern.finditer(remaining):
        func, num = step.groups()
        val = operators[func](val, int(num))
    
    return val