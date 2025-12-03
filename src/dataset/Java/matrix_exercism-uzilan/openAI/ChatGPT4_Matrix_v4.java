import java.util.ArrayList;
import java.util.List;

class Matrix {

    private final int[][] matrix;

    Matrix(String matrixAsString) {
        String[] rows = matrixAsString.split("\n");
        matrix = new int[rows.length][];
        for (int i = 0; i < rows.length; i++) {
            String[] values = rows[i].split(" ");
            matrix[i] = new int[values.length];
            for (int j = 0; j < values.length; j++) {
                matrix[i][j] = Integer.parseInt(values[j]);
            }
        }
    }

    int[] getRow(int rowNumber) {
        return matrix[rowNumber].clone();
    }

    int[] getColumn(int columnNumber) {
        int[] column = new int[matrix.length];
        for (int i = 0; i < matrix.length; i++) {
            column[i] = matrix[i][columnNumber];
        }
        return column;
    }

    int getRowsCount() {
        return matrix.length;
    }

    int getColumnsCount() {
        return matrix[0].length;
    }
}