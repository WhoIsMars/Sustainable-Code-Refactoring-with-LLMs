var Year = function(year) {
  this.year = year;
  this._isLeap = null;
}

Year.prototype.isLeap = function() {
  if (this._isLeap === null) {
    this._isLeap = (this.year & 3) === 0 && (this.year % 100 !== 0 || this.year % 400 === 0);
  }
  return this._isLeap;
}

module.exports = Year;