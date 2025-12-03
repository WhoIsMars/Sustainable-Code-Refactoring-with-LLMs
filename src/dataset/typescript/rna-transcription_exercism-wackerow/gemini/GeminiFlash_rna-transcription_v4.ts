class Transcriptor {
    toRna(dna: string) {
        let rna = "";
        for (let i = 0; i < dna.length; i++) {
            const nucleotide = dna[i];
            switch (nucleotide) {
                case "C":
                    rna += "G";
                    break;
                case "G":
                    rna += "C";
                    break;
                case "A":
                    rna += "U";
                    break;
                case "T":
                    rna += "A";
                    break;
                default:
                    throw "Invalid input DNA.";
            }
        }
        return rna;
    }
}

export default Transcriptor