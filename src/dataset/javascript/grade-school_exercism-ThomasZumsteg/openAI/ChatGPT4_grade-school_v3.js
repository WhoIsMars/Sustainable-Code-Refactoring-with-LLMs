class School {
  constructor() {
    this.class = new Map();
  }

  roster() {
    const result = {};
    for (const [grade, students] of this.class.entries()) {
      result[grade] = [...students];
    }
    return result;
  }

  grade(grade) {
    return this.class.get(grade) ? [...this.class.get(grade)] : [];
  }

  add(student, grade) {
    if (!this.class.has(grade)) {
      this.class.set(grade, new Set());
    }
    this.class.get(grade).add(student);
    this.class.set(grade, new Set([...this.class.get(grade)].sort()));
  }
}

module.exports = School;