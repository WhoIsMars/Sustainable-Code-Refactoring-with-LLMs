class Year {
  constructor(year) {
    this.year = year;
  }

  isLeap() {
    const { year } = this;
    if (year % 4 !== 0) return false;
    if (year % 100 === 0 && year % 400 !== 0) return false;
    return true;
  }
}

module.exports = Year;