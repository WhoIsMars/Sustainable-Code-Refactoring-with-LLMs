type Roster = Map<string, string[]>;

export default class GradeSchool {
  private _roster: Roster = new Map();

  public studentRoster(): Roster {
    return new Map(
      Array.from(this._roster, ([key, value]) => [key, [...value]])
    );
  }

  public studentsInGrade(grade: number): string[] {
    return this._roster.get(grade.toString())?.slice() || [];
  }

  public addStudent(name: string, grade: number): void {
    const gradeString = grade.toString();
    if (!this._roster.has(gradeString)) {
      this._roster.set(gradeString, [name]);
    } else {
      const gradeRoster = this._roster.get(gradeString)!;
      const index = gradeRoster.findIndex(student => student > name);
      if (index === -1) {
        gradeRoster.push(name);
      } else {
        gradeRoster.splice(index, 0, name);
      }
    }
  }
}