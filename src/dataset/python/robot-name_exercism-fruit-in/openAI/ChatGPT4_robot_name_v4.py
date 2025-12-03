from random import SystemRandom
from string import ascii_uppercase, digits

class Robot:
    _random = SystemRandom()
    _used_names = set()

    def __init__(self):
        self.name = None
        self.reset()

    def reset(self):
        while True:
            name = ''.join(self._random.choices(ascii_uppercase, k=2) + 
                           self._random.choices(digits, k=3))
            if name not in self._used_names:
                self._used_names.add(name)
                self.name = name
                break