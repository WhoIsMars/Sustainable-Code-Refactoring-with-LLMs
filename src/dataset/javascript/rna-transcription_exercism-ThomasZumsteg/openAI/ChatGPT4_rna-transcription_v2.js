class DnaTranscriber {
    constructor() {
        this.dnaToRna = { G: 'C', C: 'G', T: 'A', A: 'U' };
    }

    toRna(dna) {
        return [...dna].map(nucleotide => this.dnaToRna[nucleotide] || '').join('');
    }
}

module.exports = DnaTranscriber;