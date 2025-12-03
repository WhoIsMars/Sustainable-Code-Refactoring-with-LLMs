class Matrix {
    public rows: number[][];
    public columns: number[][];

    constructor(matrixString: string) {
        const splitByLine = matrixString.split('\n');
        this.rows = splitByLine.map(row => row.split(' ').map(Number));
        this.columns = this.rows[0].map((_, colIndex) => this.rows.map(row => row[colIndex]));
    }
}

export default Matrix;