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
    
    const insertIndex = this.binarySearchInsert(gradeRoster, name);
    gradeRoster.splice(insertIndex, 0, name);
  }

  public studentsInGrade(grade: number): string[] {
    const gradeRoster = this.roster.get(grade.toString());
    return gradeRoster ? gradeRoster.slice() : [];
  }

  private binarySearchInsert(arr: string[], item: string): number {
    let left = 0;
    let right = arr.length;
    
    while (left < right) {
      const mid = Math.floor((left + right) / 2);
      if (arr[mid] < item) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    
    return left;
  }
}