const DEFAULT_STUDENTS = ['Alice', 'Bob', 'Charlie', 'David', 'Eve', 
    'Fred', 'Ginny', 'Harriet', 'Ileana', 'Joseph', 'Kincaid', 'Larry'];

class Garden {
    constructor(garden, students = DEFAULT_STUDENTS) {
        const sortedStudents = [...students].sort();
        const plantMap = { C: 'clover', G: 'grass', R: 'radishes', V: 'violets' };
        const rows = garden.split('\n').map(row => [...row].map(plant => plantMap[plant]));

        sortedStudents.forEach((student, i) => {
            this[student.toLowerCase()] = [
                rows[0][2 * i], rows[0][2 * i + 1],
                rows[1][2 * i], rows[1][2 * i + 1]
            ];
        });
    }
}

module.exports = Garden;