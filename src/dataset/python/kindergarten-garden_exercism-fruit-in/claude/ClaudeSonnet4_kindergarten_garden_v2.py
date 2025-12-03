class Garden:
    STUDENTS = ["Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry", ]
    PLANTS = {"G": "Grass", "C": "Clover", "R": "Radishes", "V": "Violets", }

    def __init__(self, diagram, students=STUDENTS):
        row0, row1 = diagram.split('\n')
        students = sorted(students)
        self.cups = {}

        for i, student in enumerate(students):
            if i * 2 + 1 >= len(row0):
                break
            idx = i * 2
            seeds = [row0[idx], row0[idx + 1], row1[idx], row1[idx + 1]]
            self.cups[student] = [self.PLANTS[seed] for seed in seeds]

    def plants(self, student):
        return self.cups[student]