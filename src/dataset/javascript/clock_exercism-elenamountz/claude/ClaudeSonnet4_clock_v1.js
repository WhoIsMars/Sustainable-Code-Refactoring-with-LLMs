const maxHours = 24;
const maxMinutes = 60;

const putZero = (number) => number < 10 ? `0${number}` : `${number}`;

const at = (hours, minutes = 0) => {
  // Handle minutes overflow/underflow
  if (minutes >= maxMinutes || minutes < 0) {
    const overMinutes = Math.floor(minutes / maxMinutes);
    hours += overMinutes;
    minutes = minutes % maxMinutes;
    if (minutes < 0) minutes += maxMinutes;
  }
  
  // Handle hours overflow/underflow
  if (hours >= maxHours || hours < 0) {
    hours = hours % maxHours;
    if (hours < 0) hours += maxHours;
  }
  
  const time = `${putZero(hours)}:${putZero(minutes)}`;
  
  return {
    toString: () => time,
    plus: (number) => at(hours, minutes + number),
    minus: (number) => at(hours, minutes - number),
    equals: (aTime) => time === aTime.toString()
  };
};

export default at;