/* A class to keep track of students in a school */
var School = function() { this.class = {} };

// The entire school
School.prototype.roster = function() {
    const rosterCopy = {};
    for (const grade in this.class) {
        if (this.class.hasOwnProperty(grade)) {
            rosterCopy[grade] = [...this.class[grade]]; // Create a copy to avoid direct modification
        }
    }
    return rosterCopy;
};

// A grade level of the school
School.prototype.grade = function(grade) {
    return (this.class[grade] || []).slice(); // Return a copy to prevent modification
};

School.prototype.add = function(student, grade) {
	/* Adds students to the school */
	if( this.class[grade] ) {
		this.class[grade].push(student);
		this.class[grade].sort();
	}
	else
		this.class[grade] = [student];
};

module.exports = School;