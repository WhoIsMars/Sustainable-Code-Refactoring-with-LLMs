class Matrix {
    public rows: number[][] = [];
    public columns: number[][] = [];

    constructor(matrixString: string) {
        const rows = matrixString.split('\n');
        const numRows = rows.length;

        if (numRows > 0) {
            const firstRow = rows[0].split(' ');
            const numCols = firstRow.length;

            this.rows = Array(numRows).fill(null).map(() => Array(numCols));
            this.columns = Array(numCols).fill(null).map(() => Array(numRows));

            for (let i = 0; i < numRows; i++) {
                const rowValues = rows[i].split(' ');
                for (let j = 0; j < numCols; j++) {
                    const value = +rowValues[j];
                    this.rows[i][j] = value;
                    this.columns[j][i] = value;
                }
            }
        }
    }
}

export default Matrix;