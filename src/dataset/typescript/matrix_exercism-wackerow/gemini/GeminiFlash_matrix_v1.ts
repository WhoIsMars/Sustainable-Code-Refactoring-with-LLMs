class Matrix {
    public rows: number[][] = [];
    public columns: number[][] = [];

    constructor(matrixString: string) {
        const rowsStrings = matrixString.split('\n');
        const numRows = rowsStrings.length;

        if (numRows > 0) {
            const firstRow = rowsStrings[0].split(' ');
            const numCols = firstRow.length;

            this.rows = new Array(numRows);
            this.columns = new Array(numCols);

            for (let i = 0; i < numRows; i++) {
                this.rows[i] = new Array(numCols);
                const rowValues = rowsStrings[i].split(' ');

                for (let j = 0; j < numCols; j++) {
                    const value = +rowValues[j];
                    this.rows[i][j] = value;

                    if (!this.columns[j]) {
                        this.columns[j] = new Array(numRows);
                    }
                    this.columns[j][i] = value;
                }
            }
        }
    }
}

export default Matrix;