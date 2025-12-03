// *10^3 to milliseconds
export const gigasecond = (date) => {
  const gigasecondInMs = 1000000000000;
  return new Date(date.getTime() + gigasecondInMs);
};