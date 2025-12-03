function accumulate(items, func) {
  /* Applies a function to every item in a list */
  return items.map(func);
}

module.exports = accumulate;