class Transcriptor {
    private static readonly dnaToRnaMap: Record<string, string> = {
        C: "G",
        G: "C",
        A: "U",
        T: "A",
    };

    toRna(dna: string): string {
        return [...dna].map(nucleotide => {
            const rna = Transcriptor.dnaToRnaMap[nucleotide];
            if (!rna) throw "Invalid input DNA.";
            return rna;
        }).join('');
    }
}

export default Transcriptor;