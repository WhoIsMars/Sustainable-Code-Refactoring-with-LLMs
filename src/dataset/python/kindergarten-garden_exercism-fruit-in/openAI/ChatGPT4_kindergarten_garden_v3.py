class Garden:
    STUDENTS = ("Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry")
    PLANTS = {"G": "Grass", "C": "Clover", "R": "Radishes", "V": "Violets"}

    def __init__(self, diagram, students=STUDENTS):
        rows = diagram.splitlines()
        self.cups = {
            student: [self.PLANTS[rows[row][col]] for row in (0, 1) for col in range(i * 2, i * 2 + 2)]
            for i, student in enumerate(sorted(students))
        }

    def plants(self, student):
        return self.cups[student]