class Transcriptor {
    private static readonly DNA_TO_RNA_MAP: Record<string, string> = {
        'C': 'G',
        'G': 'C',
        'A': 'U',
        'T': 'A'
    };

    toRna(dna: string): string {
        let result = '';
        for (let i = 0; i < dna.length; i++) {
            const rna = Transcriptor.DNA_TO_RNA_MAP[dna[i]];
            if (rna === undefined) {
                throw "Invalid input DNA.";
            }
            result += rna;
        }
        return result;
    }
}

export default Transcriptor