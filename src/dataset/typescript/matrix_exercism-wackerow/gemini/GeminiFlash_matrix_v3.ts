class Matrix {
    public rows: number[][];
    public columns: number[][];

    constructor(matrixString: string) {
        const lines = matrixString.split('\n');
        const numRows = lines.length;
        this.rows = new Array(numRows);
        this.columns = [];

        for (let i = 0; i < numRows; i++) {
            const rowValues = lines[i].split(' ').map(Number);
            this.rows[i] = rowValues;

            for (let j = 0; j < rowValues.length; j++) {
                if (!this.columns[j]) {
                    this.columns[j] = [];
                }
                this.columns[j].push(rowValues[j]);
            }
        }
    }
}

export default Matrix;