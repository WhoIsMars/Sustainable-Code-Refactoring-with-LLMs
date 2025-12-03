const maxHours = 24;
const maxMinutes = 60;

const putZero = (number) => number < 10 ? `0${number}` : String(number);

const at = (hours, minutes = 0) => {
  let totalMinutes = (hours * maxMinutes) + minutes;

  totalMinutes %= (maxHours * maxMinutes);

  if (totalMinutes < 0) {
    totalMinutes += (maxHours * maxMinutes);
  }

  hours = Math.floor(totalMinutes / maxMinutes);
  minutes = totalMinutes % maxMinutes;

  const time = `${putZero(hours)}:${putZero(minutes)}`;

  return {
    toString: () => time,
    plus: (number) => at(hours, minutes + number),
    minus: (number) => at(hours, minutes - number),
    equals: (aTime) => time === aTime.toString()
  };
};

export default at;