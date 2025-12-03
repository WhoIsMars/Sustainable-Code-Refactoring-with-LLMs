import java.util.Arrays;

class Matrix {
    private int[][] matrix;
    private int rows;
    private int cols;

    Matrix(String matrixAsString) {
        String[] lines = matrixAsString.split("\n");
        this.rows = lines.length;
        this.cols = lines[0].split(" ").length;
        this.matrix = new int[rows][cols];
        
        for (int i = 0; i < rows; i++) {
            String[] values = lines[i].split(" ");
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = Integer.parseInt(values[j]);
            }
        }
    }

    int[] getRow(int rowNumber) {
        return Arrays.copyOf(matrix[rowNumber-1], cols);
    }

    int[] getColumn(int columnNumber) {
        int[] column = new int[rows];
        int colIndex = columnNumber - 1;
        for (int i = 0; i < rows; i++) {
            column[i] = matrix[i][colIndex];
        }
        return column;
    }
}