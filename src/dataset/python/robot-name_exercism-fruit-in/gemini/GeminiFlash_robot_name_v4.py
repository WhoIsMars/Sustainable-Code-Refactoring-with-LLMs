import random
import string


class Robot:
    _existing_names = set()
    _name_format = "{}{}{}{}{}"

    def __init__(self):
        self.name = self._generate_name()

    def reset(self):
        self.name = self._generate_name()

    def _generate_name(self):
        while True:
            name = self._name_format.format(
                random.choice(string.ascii_uppercase),
                random.choice(string.ascii_uppercase),
                random.choice(string.digits),
                random.choice(string.digits),
                random.choice(string.digits),
            )
            if name not in self._existing_names:
                self._existing_names.add(name)
                return name