import java.util.StringTokenizer;

class Matrix {

    private final int[][] matrix;
    private final int rows;
    private final int columns;

    Matrix(String matrixAsString) {
        String[] lines = matrixAsString.split("\n");
        rows = lines.length;
        columns = countColumns(lines[0]);
        matrix = new int[rows][columns];
        
        for (int i = 0; i < rows; i++) {
            parseRow(lines[i], matrix[i]);
        }
    }

    private int countColumns(String firstRow) {
        StringTokenizer tokenizer = new StringTokenizer(firstRow, " ");
        return tokenizer.countTokens();
    }

    private void parseRow(String row, int[] targetArray) {
        StringTokenizer tokenizer = new StringTokenizer(row, " ");
        int index = 0;
        while (tokenizer.hasMoreTokens()) {
            targetArray[index++] = Integer.parseInt(tokenizer.nextToken());
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
        return columns;
    }
}