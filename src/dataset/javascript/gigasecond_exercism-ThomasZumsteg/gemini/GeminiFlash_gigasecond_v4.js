// milliseconds
const GIGASECOND = 1e12;

const Gigasecond = function(day) {
	this.day = day;
};

Gigasecond.prototype.date = function() {
  return new Date(this.day.getTime() + GIGASECOND);
};

module.exports = Gigasecond;