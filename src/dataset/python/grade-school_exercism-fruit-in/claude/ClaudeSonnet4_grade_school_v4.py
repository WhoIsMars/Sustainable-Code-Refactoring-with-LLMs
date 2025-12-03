from collections import defaultdict

class School:
    def __init__(self):
        self.grades = defaultdict(list)
        self._roster_cache = None
        self._grade_caches = {}

    def add_student(self, name, grade):
        self.grades[grade].append(name)
        self._roster_cache = None
        self._grade_caches.pop(grade, None)

    def roster(self):
        if self._roster_cache is None:
            self._roster_cache = [name for grade in sorted(self.grades.keys()) 
                                for name in sorted(self.grades[grade])]
        return self._roster_cache[:]

    def grade(self, grade_number):
        if grade_number not in self._grade_caches:
            self._grade_caches[grade_number] = sorted(self.grades[grade_number])
        return self._grade_caches[grade_number][:]