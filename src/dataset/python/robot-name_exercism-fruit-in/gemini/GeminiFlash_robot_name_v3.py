from random import choices
from string import ascii_uppercase, digits


class Robot:
    _existing_names = set()

    def __init__(self):
        self.name = self._generate_name()

    def reset(self):
        self.name = self._generate_name()

    def _generate_name(self):
        while True:
            name = ''.join(choices(ascii_uppercase, k=2) + choices(digits, k=3))
            if name not in Robot._existing_names:
                Robot._existing_names.add(name)
                return name