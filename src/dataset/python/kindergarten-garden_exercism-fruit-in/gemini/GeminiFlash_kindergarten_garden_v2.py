class Garden:
    STUDENTS = ["Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry", ]
    PLANTS = {"G": "Grass", "C": "Clover", "R": "Radishes", "V": "Violets"}

    def __init__(self, diagram, students=STUDENTS):
        row0, row1 = diagram.split('\n')
        students = sorted(students)
        num_students = len(students)
        self.cups = {}

        for i in range(num_students):
            plant_indices = 2 * i, 2 * i + 1
            seeds = [row0[plant_indices[0]], row0[plant_indices[1]],
                     row1[plant_indices[0]], row1[plant_indices[1]]]
            self.cups[students[i]] = [self.PLANTS[seed] for seed in seeds]

    def plants(self, student):
        return self.cups[student]