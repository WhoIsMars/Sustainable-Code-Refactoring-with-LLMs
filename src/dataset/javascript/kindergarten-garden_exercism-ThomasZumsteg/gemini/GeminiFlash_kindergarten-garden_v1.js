var DEFAULT_STUDENTS = [ 'Alice', 'Bob', 'Charlie', 'David', 'Eve',
		'Fred', 'Ginny', 'Harriet', 'Ileana', 'Joseph', 'Kincaid', 'Larry'];

var Garden = function(garden, students) {
	/* A Kindergarden plant garden */
	students = students ? [...students].sort() : DEFAULT_STUDENTS;
	garden = garden.split('\n');

	for(let i = 0; i < students.length; i++) {
		const student = students[i].toLowerCase();
		const plants = [];
		for (let j = 0; j < 2; j++) {
			const rowIndex = j === 0 ? 0 : 1;
			const plant1 = garden[rowIndex][2 * i];
			const plant2 = garden[rowIndex][2 * i + 1];
			plants.push(plant_map[plant1]);
			plants.push(plant_map[plant2]);
		}
		this[student] = plants;
	}
};

const plant_map = {'C': 'clover', 'G': 'grass', 'R': 'radishes', 'V': 'violets'};

module.exports = Garden;