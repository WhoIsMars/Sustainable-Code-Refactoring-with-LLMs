var DEFAULT_STUDENTS = [ 'Alice', 'Bob', 'Charlie', 'David', 'Eve',
		'Fred', 'Ginny', 'Harriet', 'Ileana', 'Joseph', 'Kincaid', 'Larry'];

var Garden = function(garden, students) {
	/* A Kindergarden plant garden */
	students = students ? [...students].sort() : DEFAULT_STUDENTS;
	const gardenRows = garden.split('\n');
	const gardenData = gardenRows.map(row => row.split(''));

	for(let i = 0; i < students.length; i++) {
		const student = students[i].toLowerCase();
		const plants = [];
		for (const row of gardenData) {
			plants.push(row[2 * i]);
			plants.push(row[2 * i + 1]);
		}

		const plant_map = {'C': 'clover', 'G': 'grass', 'R': 'radishes', 'V': 'violets'};
		this[student] = plants.map(plant => plant_map[plant]);
	}
};

module.exports = Garden;