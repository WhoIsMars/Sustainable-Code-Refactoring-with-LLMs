type Roster = Map<string, string[]>;

export default class School {
  private roster: Roster = new Map();

  public studentRoster(): Roster {
    const newRoster: Roster = new Map();
    for (const [grade, students] of this.roster) {
      newRoster.set(grade, students.slice()); // Efficiently create a copy
    }
    return newRoster;
  }

  public addStudent(name: string, grade: number): void {
    const gradeString = grade.toString();
    let gradeRoster = this.roster.get(gradeString);

    if (!gradeRoster) {
      gradeRoster = [];
      this.roster.set(gradeString, gradeRoster);
    }

    gradeRoster.push(name);
    gradeRoster.sort();
  }

  public studentsInGrade(grade: number): string[] {
    const gradeString = grade.toString();
    const gradeRoster = this.roster.get(gradeString);
    return gradeRoster ? gradeRoster.slice() : [];
  }
}