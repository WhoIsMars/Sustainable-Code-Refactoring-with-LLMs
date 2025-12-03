var Year = function(year) {
  this.year = year;
};

Year.prototype.isLeap = function() {
  const year = this.year;
  if (year % 4 !== 0) {
    return false;
  }
  if (year % 100 === 0 && year % 400 !== 0) {
    return false;
  }
  return true;
};

module.exports = Year;