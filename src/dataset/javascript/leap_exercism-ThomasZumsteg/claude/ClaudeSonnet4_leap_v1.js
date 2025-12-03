var Year = function(year) {
  this.year = year;
  this._isLeapCached = null;
}

Year.prototype.isLeap = function() { 
  if (this._isLeapCached !== null) {
    return this._isLeapCached;
  }
  
  this._isLeapCached = (this.year & 3) === 0 && (this.year % 100 !== 0 || this.year % 400 === 0);
  return this._isLeapCached;
}

module.exports = Year;