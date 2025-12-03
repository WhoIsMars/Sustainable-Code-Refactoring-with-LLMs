class Raindrops {
  convert(number) {
    const factors = [
      [3, 'Pling'],
      [5, 'Plang'],
      [7, 'Plong']
    ];
    let output = factors.reduce((acc, [factor, sound]) => number % factor === 0 ? acc + sound : acc, '');
    return output || number.toString();
  }
}

export default Raindrops;