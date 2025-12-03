const DEFAULT_STUDENTS = ['Alice', 'Bob', 'Charlie', 'David', 'Eve', 
    'Fred', 'Ginny', 'Harriet', 'Ileana', 'Joseph', 'Kincaid', 'Larry'];

class Garden {
    constructor(garden, students = DEFAULT_STUDENTS) {
        this.students = [...students].sort().map(student => student.toLowerCase());
        this.gardenRows = garden.split('\n');
        this.plantMap = { 'C': 'clover', 'G': 'grass', 'R': 'radishes', 'V': 'violets' };

        this.students.forEach((student, index) => {
            this[student] = this.getStudentPlants(index);
        });
    }

    getStudentPlants(position) {
        const plants = [];
        for (const row of this.gardenRows) {
            plants.push(this.plantMap[row[2 * position]], this.plantMap[row[2 * position + 1]]);
        }
        return plants;
    }
}

module.exports = Garden;