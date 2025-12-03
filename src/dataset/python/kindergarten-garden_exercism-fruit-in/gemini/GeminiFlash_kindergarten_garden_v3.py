class Garden:
    STUDENTS = ["Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry", ]
    PLANTS = {"G": "Grass", "C": "Clover", "R": "Radishes", "V": "Violets", }

    def __init__(self, diagram, students=STUDENTS):
        row0, row1 = diagram.split('\n')
        students = sorted(students)
        num_students = len(students)
        self.cups = {}

        for i in range(min(num_students, len(row0) // 2)):
            student = students[i]
            seeds = (row0[2 * i], row0[2 * i + 1],
                     row1[2 * i], row1[2 * i + 1])
            self.cups[student] = [self.PLANTS[seed] for seed in seeds]

    def plants(self, student):
        return self.cups[student]