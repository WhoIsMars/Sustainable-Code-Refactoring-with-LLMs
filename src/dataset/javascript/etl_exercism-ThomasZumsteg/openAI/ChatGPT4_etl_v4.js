class ETL {
  transform(oldStruct) {
    const newStruct = {};
    for (const [key, values] of Object.entries(oldStruct)) {
      for (const val of values) {
        newStruct[val.toLowerCase()] = +key;
      }
    }
    return newStruct;
  }
}

module.exports = ETL;