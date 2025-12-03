class Garden:
    STUDENTS = ("Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry")
    PLANTS = {"G": "Grass", "C": "Clover", "R": "Radishes", "V": "Violets"}

    def __init__(self, diagram, students=STUDENTS):
        row0, row1 = diagram.split('\n')
        students = tuple(sorted(students))
        self.cups = {}
        
        plants_get = self.PLANTS.get
        
        for i, student in enumerate(students):
            if i * 2 + 1 >= len(row0):
                break
            idx = i * 2
            self.cups[student] = (
                plants_get(row0[idx]),
                plants_get(row0[idx + 1]),
                plants_get(row1[idx]),
                plants_get(row1[idx + 1])
            )

    def plants(self, student):
        return self.cups[student]