"""Does a natrual language calculation"""
from operator import add, sub, mul, truediv
from re import compile

def calculate(string):
    """Parses and preforms natrual language calculation"""
    operators = {"plus": add,
                 "minus": sub,
                 "multiplied by": mul,
                 "divided by": truediv,
                }
    
    # Pre-compile regex pattern for better performance
    pattern = compile(r"What is (-?\d+)((?:(?:plus|minus|multiplied by|divided by) (-?\d+))+)\?$")
    
    match_obj = pattern.match(string)
    if not match_obj:
        raise ValueError
    
    val = int(match_obj.group(1))
    remaining = match_obj.group(2)
    
    # Pre-compile the step pattern
    step_pattern = compile(r" (plus|minus|multiplied by|divided by) (-?\d+)")
    
    for step in step_pattern.finditer(remaining):
        func, num = step.groups()
        val = operators[func](val, int(num))
    
    return val