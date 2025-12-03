import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

class Matrix {

    private final int[][] matrix;
    private final int rows;
    private final int cols;

    Matrix(String matrixAsString) {
        String[] rowsAsString = matrixAsString.split("\n");
        this.rows = rowsAsString.length;

        String[] firstRow = rowsAsString[0].split(" ");
        this.cols = firstRow.length;

        this.matrix = new int[this.rows][this.cols];

        for (int i = 0; i < this.rows; i++) {
            String[] elements = rowsAsString[i].split(" ");
            for (int j = 0; j < this.cols; j++) {
                this.matrix[i][j] = Integer.parseInt(elements[j]);
            }
        }
    }

    int[] getRow(int rowNumber) {
        return Arrays.copyOf(matrix[rowNumber], cols);
    }

    int[] getColumn(int columnNumber) {
        int[] column = new int[rows];
        for (int i = 0; i < rows; i++) {
            column[i] = matrix[i][columnNumber];
        }
        return column;
    }

    int getRowsCount() {
        return rows;
    }

    int getColumnsCount() {
        return cols;
    }
}