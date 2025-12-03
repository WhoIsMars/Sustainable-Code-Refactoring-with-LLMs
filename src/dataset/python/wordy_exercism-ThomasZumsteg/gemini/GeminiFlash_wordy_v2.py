"""Does a natrual language calculation"""
from operator import add, sub, mul, truediv
import re

def calculate(string):
    """Parses and preforms natrual language calculation"""
    operators = {"plus": add,
                 "minus": sub,
                 "multiplied by": mul,
                 "divided by": truediv,
                }
    start = "What is"
    function_pattern = " (" + "|".join(operators.keys()) + ")"
    number_pattern = r" (-?\d+)"
    regex_pattern = start + "(?P<first>" + number_pattern + ")" + "(?P<calculation>" +\
            "(" + function_pattern + number_pattern + ")+)" + r"\?$"
    regex = re.compile(regex_pattern)
    regex_match = regex.match(string)
    if not regex_match:
        raise ValueError
    val = int(regex_match.group('first'))
    remaining = regex_match.group('calculation')
    
    function_number_pattern = re.compile(function_pattern + number_pattern)
    for step in function_number_pattern.finditer(remaining):
        func, num = step.groups()
        val = operators[func](val, int(num))
    return val