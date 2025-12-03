class Raindrops {
  convert(number) {
    const factors = [
      [3, 'Pling'],
      [5, 'Plang'],
      [7, 'Plong']
    ];
    
    let output = '';
    for (const [factor, sound] of factors) {
      if (number % factor === 0) {
        output += sound;
      }
    }
    
    return output || number.toString();
  }
}

export default Raindrops;