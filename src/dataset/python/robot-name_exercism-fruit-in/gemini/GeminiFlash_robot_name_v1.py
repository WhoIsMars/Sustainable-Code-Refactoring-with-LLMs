import random
import string


class Robot:
    _existing_names = set()

    def __init__(self):
        self.name = self._generate_name()

    def _generate_name(self):
        while True:
            name = ''.join(random.choices(string.ascii_uppercase, k=2) +
                           random.choices(string.digits, k=3))
            if name not in Robot._existing_names:
                Robot._existing_names.add(name)
                return name

    def reset(self):
        self.name = self._generate_name()