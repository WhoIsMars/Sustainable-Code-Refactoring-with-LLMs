// milliseconds - precomputed constant
const GIGASECOND = 1000000000000;

const Gigasecond = function(day) {
	this.day = day;
};

Gigasecond.prototype.date = function() { 
  return new Date(this.day.getTime() + GIGASECOND);
};

module.exports = Gigasecond;