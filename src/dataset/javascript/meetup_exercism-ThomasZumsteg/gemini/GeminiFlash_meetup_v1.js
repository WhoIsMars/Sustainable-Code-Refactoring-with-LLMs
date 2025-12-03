var weekDays = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];

var Meetup = function(year, month, day, nth) {
  const intDay = weekDays.indexOf(day);

  if (intDay === -1) {
    throw new Error("Invalid day of the week");
  }

  switch (nth) {
    case "teenth":
      return findDay(year, month, intDay, 13, 19);
    case "1st":
      return findDay(year, month, intDay, 1, 7);
    case "2nd":
      return findDay(year, month, intDay, 8, 14);
    case "3rd":
      return findDay(year, month, intDay, 15, 21);
    case "4th":
      return findDay(year, month, intDay, 22, 28);
    case "5th":
      return findDay(year, month, intDay, 29, 31);
    case "last":
      return findLast(year, month, intDay);
    default:
      throw new Error("Invalid nth day");
  }
};

function findDay(year, month, day, start, stop) {
  for (let date = start; date <= stop; date++) {
    const meetup = new Date(year, month, date);
    if (meetup.getMonth() === month && meetup.getDay() === day) {
      return meetup;
    }
  }
  throw new Error("No such date exists");
}

function findLast(year, month, day) {
  let lastDayOfMonth = new Date(year, month + 1, 0).getDate();

  for (let date = lastDayOfMonth; date >= 1; date--) {
    const meetup = new Date(year, month, date);
    if (meetup.getMonth() === month && meetup.getDay() === day) {
      return meetup;
    }
  }
  throw new Error("No such date exists");
}

module.exports = Meetup;