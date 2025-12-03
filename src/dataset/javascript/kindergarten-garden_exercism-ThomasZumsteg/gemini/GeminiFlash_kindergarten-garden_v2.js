var DEFAULT_STUDENTS = [ 'Alice', 'Bob', 'Charlie', 'David', 'Eve',
		'Fred', 'Ginny', 'Harriet', 'Ileana', 'Joseph', 'Kincaid', 'Larry'];

var Garden = function(garden, students) {
	/* A Kindergarden plant garden */
	students = students ? [...students].sort() : [...DEFAULT_STUDENTS];
	const gardenRows = garden.split('\n');
	const gardenPlan = gardenRows.map(row => MakeRow(row));

	for(let i = 0; i < students.length; i++) {
		const student = students[i].toLowerCase();
		this[student] = StudentsGarden(gardenPlan, i);
	}
};

const plant_map = {'C': 'clover', 'G': 'grass', 'R': 'radishes', 'V': 'violets'};

function MakeRow(row) {
	/* Converts a row of plant letters to an array of plants */
	const plants = [];
	for (let i = 0; i < row.length; i++) {
		plants.push(plant_map[row[i]]);
	}
	return plants;
}

function StudentsGarden(garden, position) {
	/* The plants owned by an individual student */
	const plants = [];
	for (let i = 0; i < garden.length; i++) {
		plants.push(garden[i][2 * position]);
		plants.push(garden[i][2 * position + 1]);
	}
	return plants;
}

module.exports = Garden;