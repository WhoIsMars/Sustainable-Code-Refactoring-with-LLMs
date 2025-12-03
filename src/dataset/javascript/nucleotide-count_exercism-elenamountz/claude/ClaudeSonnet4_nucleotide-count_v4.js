class NucleotideCounts{
  constructor(){}

  static parse(dna){
    if(dna === ''){
      return '0 0 0 0';
    }

    const counts = [0, 0, 0, 0];
    const nucleotideMap = { 'A': 0, 'C': 1, 'G': 2, 'T': 3 };

    for(let i = 0; i < dna.length; i++){
      const index = nucleotideMap[dna[i]];
      if(index === undefined){
        throw new Error('Invalid nucleotide in strand');
      }
      counts[index]++;
    }

    return counts.join(' ');
  }
}

export default NucleotideCounts;