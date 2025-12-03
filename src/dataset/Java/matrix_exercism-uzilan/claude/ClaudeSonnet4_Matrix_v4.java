import java.util.Arrays;

class Matrix {

    private final int[][] matrix;
    private final int rows;
    private final int columns;

    Matrix(String matrixAsString) {
        String[] lines = matrixAsString.split("\n");
        this.rows = lines.length;
        this.columns = lines[0].split(" ").length;
        this.matrix = new int[rows][columns];
        
        for (int i = 0; i < rows; i++) {
            String[] values = lines[i].split(" ");
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = Integer.parseInt(values[j]);
            }
        }
    }

    int[] getRow(int rowNumber) {
        return Arrays.copyOf(matrix[rowNumber], columns);
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
        return columns;
    }
}