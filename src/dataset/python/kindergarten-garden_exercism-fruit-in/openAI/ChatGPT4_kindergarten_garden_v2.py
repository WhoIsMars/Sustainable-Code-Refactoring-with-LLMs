class Garden:
    STUDENTS = ("Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry")
    PLANTS = {"G": "Grass", "C": "Clover", "R": "Radishes", "V": "Violets"}

    def __init__(self, diagram, students=STUDENTS):
        rows = diagram.splitlines()
        students = sorted(students)
        self.cups = {
            students[i]: [self.PLANTS[rows[row][2 * i + col]] 
                          for row in range(2) for col in range(2)]
            for i in range(len(rows[0]) // 2)
        }

    def plants(self, student):
        return self.cups.get(student, [])