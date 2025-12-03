const maxHours = 24;
const maxMinutes = 60;

const putZero = (number) => (number < 10 ? `0${number}` : number);

const at = (hours, minutes = 0) => {
  let totalMinutes = hours * maxMinutes + minutes;

  totalMinutes %= (maxHours * maxMinutes);

  if (totalMinutes < 0) {
    totalMinutes += (maxHours * maxMinutes);
  }

  const finalHours = Math.floor(totalMinutes / maxMinutes);
  const finalMinutes = totalMinutes % maxMinutes;

  const time = `${putZero(finalHours)}:${putZero(finalMinutes)}`;

  const obj = {
    toString: () => time,
    plus: (number) => at(finalHours, finalMinutes + number),
    minus: (number) => at(finalHours, finalMinutes - number),
    equals: (aTime) => time === aTime.toString(),
  };

  return obj;
};

export default at;