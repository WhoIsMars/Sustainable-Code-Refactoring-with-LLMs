type Roster = Map<string, string[]>;

export default class GradeSchool {
  private _roster: Roster = new Map();

  public studentRoster(): Roster {
    const clone: Roster = new Map();
    for (const [grade, students] of this._roster) {
      clone.set(grade, students.slice());
    }
    return clone;
  }

  public studentsInGrade(grade: number): string[] {
    const students = this._roster.get(grade.toString());
    return students ? [...students] : [];
  }

  public addStudent(name: string, grade: number): void {
    const gradeString = grade.toString();
    let gradeRoster = this._roster.get(gradeString);

    if (!gradeRoster) {
      gradeRoster = [];
      this._roster.set(gradeString, gradeRoster);
    }

    gradeRoster.push(name);
    gradeRoster.sort();
  }
}