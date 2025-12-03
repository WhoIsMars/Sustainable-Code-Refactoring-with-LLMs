class Raindrops {
  convert(number) {
    const sounds = [
      { factor: 3, sound: 'Pling' },
      { factor: 5, sound: 'Plang' },
      { factor: 7, sound: 'Plong' }
    ];
    const output = sounds.reduce((acc, { factor, sound }) => 
      number % factor === 0 ? acc + sound : acc, 
      ''
    );
    return output || number.toString();
  }
}

export default Raindrops;