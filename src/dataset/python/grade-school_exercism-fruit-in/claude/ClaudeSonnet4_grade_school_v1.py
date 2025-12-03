class School:
    def __init__(self):
        self.grades = {}
        self._roster_cache = None
        self._grade_caches = {}

    def add_student(self, name, grade):
        if grade not in self.grades:
            self.grades[grade] = []
        self.grades[grade].append(name)
        # Invalidate caches
        self._roster_cache = None
        if grade in self._grade_caches:
            del self._grade_caches[grade]

    def roster(self):
        if self._roster_cache is None:
            result = []
            for grade in sorted(self.grades.keys()):
                result.extend(sorted(self.grades[grade]))
            self._roster_cache = result
        return self._roster_cache[:]

    def grade(self, grade_number):
        if grade_number not in self._grade_caches:
            self._grade_caches[grade_number] = sorted(self.grades.get(grade_number, []))
        return self._grade_caches[grade_number][:]