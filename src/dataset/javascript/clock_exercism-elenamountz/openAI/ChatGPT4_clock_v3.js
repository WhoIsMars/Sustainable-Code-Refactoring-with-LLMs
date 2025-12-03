const maxHours = 24;
const maxMinutes = 60;

const putZero = (number) => (number < 10 ? `0${number}` : number);

const at = (hours, minutes = 0) => {
  minutes = ((hours * maxMinutes + minutes) % (maxHours * maxMinutes) + maxHours * maxMinutes) % (maxHours * maxMinutes);
  hours = Math.floor(minutes / maxMinutes) % maxHours;
  minutes %= maxMinutes;

  const time = `${putZero(hours)}:${putZero(minutes)}`;
  return {
    toString: () => time,
    plus: (number) => at(hours, minutes + number),
    minus: (number) => at(hours, minutes - number),
    equals: (aTime) => time === (typeof aTime === 'string' ? aTime : aTime.toString()),
  };
};

export default at;