const GIGASECOND = 1e12;

function Gigasecond(day) {
  this.day = day;
}

Gigasecond.prototype.date = function() {
  const initialTime = this.day.getTime();
  return new Date(initialTime + GIGASECOND);
};

module.exports = Gigasecond;