class Matrix {
    public rows: number[][] = [];
    public columns: number[][] = [];

    constructor(matrixString: string) {
        const splitByLine = matrixString.split('\n');
        const numRows = splitByLine.length;
        const numCols = splitByLine[0]?.split(' ').length || 0;
        
        this.rows = new Array(numRows);
        this.columns = new Array(numCols);
        
        for (let j = 0; j < numCols; j++) {
            this.columns[j] = new Array(numRows);
        }
        
        for (let i = 0; i < numRows; i++) {
            const splitBySpaces = splitByLine[i].split(' ');
            this.rows[i] = new Array(numCols);
            
            for (let j = 0; j < numCols; j++) {
                const value = +splitBySpaces[j];
                this.rows[i][j] = value;
                this.columns[j][i] = value;
            }
        }
    }
}

export default Matrix;