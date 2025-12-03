import java.util.Arrays;

class Matrix {
    private final int[][] matrix;
    private final int rows;
    private final int cols;

    Matrix(String matrixAsString) {
        String[] rowsStr = matrixAsString.split("\n");
        this.rows = rowsStr.length;
        String[] firstRow = rowsStr[0].split(" ");
        this.cols = firstRow.length;

        this.matrix = new int[rows][cols];

        for (int i = 0; i < rows; i++) {
            String[] elements = rowsStr[i].split(" ");
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = Integer.parseInt(elements[j]);
            }
        }
    }

    int[] getRow(int rowNumber) {
        return Arrays.copyOf(matrix[rowNumber-1], cols);
    }

    int[] getColumn(int columnNumber) {
        int[] column = new int[rows];
        for (int i = 0; i < rows; i++) {
            column[i] = matrix[i][columnNumber-1];
        }
        return column;
    }
}