const DEFAULT_STUDENTS = ['Alice', 'Bob', 'Charlie', 'David', 'Eve', 
		'Fred', 'Ginny', 'Harriet', 'Ileana', 'Joseph', 'Kincaid', 'Larry'];

const PLANT_MAP = Object.freeze({
	'C': 'clover', 
	'G': 'grass', 
	'R': 'radishes', 
	'V': 'violets'
});

var Garden = function(garden, students) {
	const sortedStudents = students ? students.slice().sort() : DEFAULT_STUDENTS;
	const rows = garden.split('\n');
	const gardenRows = new Array(rows.length);
	
	for (let i = 0; i < rows.length; i++) {
		gardenRows[i] = MakeRow(rows[i]);
	}

	for (let i = 0; i < sortedStudents.length; i++) {
		this[sortedStudents[i].toLowerCase()] = StudentsGarden(gardenRows, i);
	}
};

function MakeRow(row) {
	const plants = new Array(row.length);
	for (let i = 0; i < row.length; i++) {
		plants[i] = PLANT_MAP[row[i]];
	}
	return plants;
}

function StudentsGarden(garden, position) {
	const startPos = position << 1;
	const endPos = startPos + 2;
	const result = new Array(garden.length << 1);
	let resultIndex = 0;
	
	for (let i = 0; i < garden.length; i++) {
		const row = garden[i];
		result[resultIndex++] = row[startPos];
		result[resultIndex++] = row[endPos - 1];
	}
	
	return result;
}

module.exports = Garden;