// [0 1 2 3]
// [A C G T]

class NucleotideCounts{
  constructor(){}

  static parse(dna){
    if(dna === ''){
      return '0 0 0 0';
    }

    const counts = [0, 0, 0, 0];
    
    for(let i = 0; i < dna.length; i++){
      const nucleotide = dna[i];
      switch(nucleotide){
        case 'A':
          counts[0]++;
          break;
        case 'C':
          counts[1]++;
          break;
        case 'G':
          counts[2]++;
          break;
        case 'T':
          counts[3]++;
          break;
        default:
          throw new Error('Invalid nucleotide in strand');
      }
    }

    return counts.join(' ');
  }
}

export default NucleotideCounts;