import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Matrix {

    private final int[][] matrix;
    private final int rowsCount;
    private final int columnsCount;

    Matrix(String matrixAsString) {
        String[] rows = matrixAsString.split("\n");
        rowsCount = rows.length;
        String[] firstRowValues = rows[0].split(" ");
        columnsCount = firstRowValues.length;

        matrix = new int[rowsCount][columnsCount];

        for (int i = 0; i < rowsCount; i++) {
            String[] values = rows[i].split(" ");
            for (int j = 0; j < columnsCount; j++) {
                matrix[i][j] = Integer.parseInt(values[j]);
            }
        }
    }

    int[] getRow(int rowNumber) {
        return Arrays.copyOf(matrix[rowNumber], columnsCount);
    }

    int[] getColumn(int columnNumber) {
        int[] column = new int[rowsCount];
        for (int i = 0; i < rowsCount; i++) {
            column[i] = matrix[i][columnNumber];
        }
        return column;
    }

    int getRowsCount() {
        return rowsCount;
    }

    int getColumnsCount() {
        return columnsCount;
    }
}