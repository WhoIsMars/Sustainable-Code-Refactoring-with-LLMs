from collections import defaultdict
from bisect import insort

class School:
    def __init__(self):
        self.grades = defaultdict(list)

    def add_student(self, name, grade):
        insort(self.grades[grade], name)

    def roster(self):
        return [name for grade in sorted(self.grades) for name in self.grades[grade]]

    def grade(self, grade_number):
        return self.grades[grade_number]