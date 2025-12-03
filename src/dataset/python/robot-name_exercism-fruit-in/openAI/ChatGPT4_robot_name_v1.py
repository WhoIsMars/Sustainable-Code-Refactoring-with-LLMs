from random import randint


class Robot:
    def __init__(self):
        self.name = ''
        self.old_names = set()
        self.reset()

    def reset(self):
        while True:
            self.name = f"{chr(randint(65, 90))}{chr(randint(65, 90))}{randint(0, 999):03}"
            if self.name not in self.old_names:
                self.old_names.add(self.name)
                break