type Roster = Map<string, string[]>;

export default class {
  private roster: Roster = new Map();

  public studentRoster(): Roster {
    return new Map(this.roster);
  }

  public addStudent(name: string, grade: number): void {
    const gradeString = grade.toString();
    if (!this.roster.has(gradeString)) {
      this.roster.set(gradeString, []);
    }
    const gradeRoster = this.roster.get(gradeString)!;
    const index = gradeRoster.findIndex(student => student > name);
    if (index === -1) {
      gradeRoster.push(name);
    } else {
      gradeRoster.splice(index, 0, name);
    }
  }

  public studentsInGrade(grade: number): string[] {
    return this.roster.get(grade.toString())?.slice() || [];
  }
}