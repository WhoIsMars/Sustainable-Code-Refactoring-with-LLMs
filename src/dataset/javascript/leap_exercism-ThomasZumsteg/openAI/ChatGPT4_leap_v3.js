class Year {
  constructor(year) {
    this.year = year;
  }

  isLeap() {
    const { year } = this;
    return (year % 4 === 0) && (year % 100 !== 0 || year % 400 === 0);
  }
}

module.exports = Year;