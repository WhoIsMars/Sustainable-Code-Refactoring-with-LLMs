class Matrix {
    public rows: number[][];
    public columns: number[][];

    constructor(matrixString: string) {
        const lines = matrixString.split('\n');
        const numRows = lines.length;
        const numCols = lines[0].split(' ').length;
        
        // Pre-allocate arrays with known dimensions
        this.rows = new Array(numRows);
        this.columns = new Array(numCols);
        
        for (let j = 0; j < numCols; j++) {
            this.columns[j] = new Array(numRows);
        }
        
        for (let i = 0; i < numRows; i++) {
            const values = lines[i].split(' ');
            this.rows[i] = new Array(numCols);
            
            for (let j = 0; j < numCols; j++) {
                const value = +values[j];
                this.rows[i][j] = value;
                this.columns[j][i] = value;
            }
        }
    }
}

export default Matrix;