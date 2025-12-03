class Transcriptor {
    private static readonly dnaToRnaMap: { [key: string]: string } = {
        "C": "G",
        "G": "C",
        "A": "U",
        "T": "A"
    };

    toRna(dna: string): string {
        let rna = "";
        for (let i = 0; i < dna.length; i++) {
            const nucleotide = dna[i];
            const rnaNucleotide = Transcriptor.dnaToRnaMap[nucleotide];
            if (rnaNucleotide === undefined) {
                throw "Invalid input DNA.";
            }
            rna += rnaNucleotide;
        }
        return rna;
    }
}

export default Transcriptor