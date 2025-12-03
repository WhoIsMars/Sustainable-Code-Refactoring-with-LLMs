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
    start = "What is"
    function_names = " (" + "|".join(operators.keys()) + ")"
    number = r" (-?\d+)"
    regex = compile(start + "(?P<first>" + number + ")" + "(?P<calculation>" +\
            "(" + function_names + number + ")+)" + r"\?$")
    regex_match = regex.match(string)
    if not regex_match:
        raise ValueError
    val = int(regex_match.group('first'))
    remaining = regex_match.group('calculation')
    function_number_regex = compile(function_names + number)
    for step in function_number_regex.finditer(remaining):
        func, num = step.groups()
        val = operators[func](val, int(num))
    return val