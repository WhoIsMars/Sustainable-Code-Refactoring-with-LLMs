import java.util.Arrays;
import java.util.List;

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

    private List<Integer> parseRow(String row) {
        return Arrays.stream(row.split(" "))
                .mapToInt(Integer::parseInt)
                .boxed()
                .collect(java.util.stream.Collectors.toList());
    }

    int[] getRow(int rowNumber) {
        return matrix[rowNumber].clone();
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