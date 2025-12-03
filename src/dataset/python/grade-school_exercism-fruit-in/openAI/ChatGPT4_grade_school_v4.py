from collections import defaultdict
from itertools import chain

class School:
    def __init__(self):
        self.grades = defaultdict(list)

    def add_student(self, name, grade):
        self.grades[grade].append(name)

    def roster(self):
        return list(chain.from_iterable(sorted(self.grades[grade]) for grade in sorted(self.grades)))

    def grade(self, grade_number):
        return sorted(self.grades[grade_number])