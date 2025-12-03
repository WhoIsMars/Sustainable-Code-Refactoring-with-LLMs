const weekDays = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];

const Meetup = function (year, month, day, nth) {
  const intDay = weekDays.indexOf(day);
  const ranges = {
    teenth: [13, 19],
    "1st": [1, 7],
    "2nd": [8, 14],
    "3rd": [15, 21],
    "4th": [22, 28],
    "5th": [29, 31],
  };

  if (nth === "last") {
    return findLastDay(year, month, intDay);
  }

  const range = ranges[nth];
  if (range) {
    return findDayInRange(year, month, intDay, range[0], range[1]);
  }

  throw new Error("Invalid nth value");
};

function findDayInRange(year, month, day, start, stop) {
  const startDate = new Date(year, month, start);
  const endDate = new Date(year, month, stop);

  for (let date = startDate; date <= endDate && date.getMonth() === month; date.setDate(date.getDate() + 1)) {
    if (date.getDay() === day) {
      return new Date(date); // Return a new Date object to avoid mutation
    }
  }

  throw new Error("Date does not exist");
}

function findLastDay(year, month, day) {
  const lastDate = new Date(year, month + 1, 0);

  for (let date = lastDate; date.getMonth() === month; date.setDate(date.getDate() - 1)) {
    if (date.getDay() === day) {
      return new Date(date); // Return a new Date object to avoid mutation
    }
  }

  throw new Error("Date does not exist");
}

module.exports = Meetup;