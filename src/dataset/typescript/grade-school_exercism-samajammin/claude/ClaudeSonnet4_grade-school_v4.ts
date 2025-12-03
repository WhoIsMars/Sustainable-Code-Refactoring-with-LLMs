type Roster = Map<string, string[]>;

export default class GradeSchool {
  private _roster: Roster = new Map();

  public studentRoster(): Roster {
    const clone = new Map<string, string[]>();
    for (const [key, value] of this._roster) {
      clone.set(key, value.slice());
    }
    return clone;
  }

  public studentsInGrade(grade: number): string[] {
    return this._roster.get(grade.toString())?.slice() ?? [];
  }

  public addStudent(name: string, grade: number): void {
    const gradeString = grade.toString();
    const gradeRoster = this._roster.get(gradeString);
    
    if (gradeRoster) {
      const insertIndex = this.findInsertIndex(gradeRoster, name);
      gradeRoster.splice(insertIndex, 0, name);
    } else {
      this._roster.set(gradeString, [name]);
    }
  }

  private findInsertIndex(sortedArray: string[], name: string): number {
    let left = 0;
    let right = sortedArray.length;
    
    while (left < right) {
      const mid = (left + right) >>> 1;
      if (sortedArray[mid] < name) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    
    return left;
  }
}