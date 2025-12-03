class Raindrops {
  convert(number) {
    const divisors = [
      [3, 'Pling'],
      [5, 'Plang'],
      [7, 'Plong']
    ];
    
    let output = '';
    for (const [divisor, sound] of divisors) {
      if (number % divisor === 0) {
        output += sound;
      }
    }
    
    return output || number.toString();
  }
}

export default Raindrops;