const maxHours = 24;
const maxMinutes = 60;

const putZero = (number) => number < 10 ? `0${number}` : String(number);

const at = (hours, minutes = 0) => {
  let totalMinutes = (hours * maxMinutes + minutes) % (maxHours * maxMinutes);
  if (totalMinutes < 0) {
    totalMinutes += maxHours * maxMinutes;
  }

  hours = Math.floor(totalMinutes / maxMinutes);
  minutes = totalMinutes % maxMinutes;

  const time = `${putZero(hours)}:${putZero(minutes)}`;

  const plus = (number) => {
    let newTotalMinutes = (totalMinutes + number) % (maxHours * maxMinutes);
    if (newTotalMinutes < 0) {
      newTotalMinutes += maxHours * maxMinutes;
    }
    const newHours = Math.floor(newTotalMinutes / maxMinutes);
    const newMinutes = newTotalMinutes % maxMinutes;
    return at(newHours, newMinutes);
  };

  const minus = (number) => {
    let newTotalMinutes = (totalMinutes - number) % (maxHours * maxMinutes);
    if (newTotalMinutes < 0) {
      newTotalMinutes += maxHours * maxMinutes;
    }
    const newHours = Math.floor(newTotalMinutes / maxMinutes);
    const newMinutes = newTotalMinutes % maxMinutes;
    return at(newHours, newMinutes);
  };

  return {
    toString: () => time,
    plus: plus,
    minus: minus,
    equals: (aTime) => time === aTime.toString()
  };
};

export default at;