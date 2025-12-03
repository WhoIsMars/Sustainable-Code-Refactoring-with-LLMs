const DEFAULT_STUDENTS = ['Alice', 'Bob', 'Charlie', 'David', 'Eve', 
    'Fred', 'Ginny', 'Harriet', 'Ileana', 'Joseph', 'Kincaid', 'Larry'];

const plantMap = { 'C': 'clover', 'G': 'grass', 'R': 'radishes', 'V': 'violets' };

function Garden(garden, students = DEFAULT_STUDENTS) {
    const sortedStudents = [...students].sort();
    const rows = garden.split('\n');
    const row1 = rows[0];
    const row2 = rows[1];

    sortedStudents.forEach((student, i) => {
        const position = i * 2;
        this[student.toLowerCase()] = [
            plantMap[row1[position]], 
            plantMap[row1[position + 1]], 
            plantMap[row2[position]], 
            plantMap[row2[position + 1]]
        ];
    });
}

module.exports = Garden;