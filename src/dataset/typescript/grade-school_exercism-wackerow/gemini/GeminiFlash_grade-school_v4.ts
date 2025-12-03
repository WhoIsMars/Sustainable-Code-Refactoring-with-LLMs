type Roster = Map<string, string[]>;

export default class {
  private roster: Roster = new Map();

  public studentRoster(): Roster {
    const newRoster: Roster = new Map();
    for (const [key, value] of this.roster) {
      newRoster.set(key, value.slice());
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