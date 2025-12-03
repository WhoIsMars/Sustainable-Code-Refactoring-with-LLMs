import java.util.ArrayList;
import java.util.List;

class Matrix {

    private final int[][] matrix;

    Matrix(String matrixAsString) {
        String[] rows = matrixAsString.split("\n");
        matrix = new int[rows.length][];
        for (int i = 0; i < rows.length; i++) {
            matrix[i] = parseRow(rows[i]);
        }
    }

    private int[] parseRow(String row) {
        String[] values = row.split(" ");
        int[] parsedRow = new int[values.length];
        for (int i = 0; i < values.length; i++) {
            parsedRow[i] = Integer.parseInt(values[i]);
        }
        return parsedRow;
    }

    int[] getRow(int rowNumber) {
        return matrix[rowNumber];
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