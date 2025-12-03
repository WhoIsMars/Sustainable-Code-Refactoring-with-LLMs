const putZero = (number) => number < 10 ? `0${number}` : number;

const at = (hours, minutes = 0) => {
  if (minutes >= 60 || minutes < 0) {
    const overMinutes = Math.floor(minutes / 60);
    hours += overMinutes;
    minutes = minutes % 60;
    if (minutes < 0) minutes += 60;
  }
  
  if (hours >= 24 || hours < 0) {
    hours = hours % 24;
    if (hours < 0) hours += 24;
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