import java.util.StringTokenizer;

class Matrix {

    private final int[][] matrix;
    private final int rows;
    private final int cols;

    Matrix(String matrixAsString) {
        String[] lines = matrixAsString.split("\n");
        rows = lines.length;
        cols = countColumns(lines[0]);
        matrix = new int[rows][cols];
        
        for (int i = 0; i < rows; i++) {
            parseRow(lines[i], matrix[i]);
        }
    }

    private int countColumns(String row) {
        StringTokenizer tokenizer = new StringTokenizer(row, " ");
        return tokenizer.countTokens();
    }

    private void parseRow(String row, int[] target) {
        StringTokenizer tokenizer = new StringTokenizer(row, " ");
        int index = 0;
        while (tokenizer.hasMoreTokens()) {
            target[index++] = Integer.parseInt(tokenizer.nextToken());
        }
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
        return cols;
    }
}