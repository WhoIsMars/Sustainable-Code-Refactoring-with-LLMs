import java.util.ArrayList;
import java.util.List;

public class PascalsTriangleGenerator {

    private int[][] triangle;

    public int[][] generateTriangle(int rows) {
        if (rows < 0) {
            throw new IllegalArgumentException("Number of rows may not be negative");
        }

        triangle = new int[rows][];
        createTheTriangel(rows);
        manipulateTriangleValues(rows);
        return triangle;
    }

    private void createTheTriangel(int rows) {
        for (int i = 0; i < rows; i++) {
            triangle[i] = new int[i + 1];
            for (int j = 0; j <= i; j++) {
                triangle[i][j] = 1;
            }
        }
    }

    private void manipulateTriangleValues(int rows) {
        for (int row = 2; row < rows; row++) {
            for (int col = 1; col < row; col++) {
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
        }
    }

    private int[][] getTheTriangleAsDoubleArray() {
        return triangle;
    }

    private void recalculateCellValue(int r, int c) {
        triangle[r][c] = addParentsValues(r, c);
    }

    private int addParentsValues(int row, int col) {
        if (row == 0 && col == 0) {
            return 1;
        }
        return getAt(row - 1, col - 1) + getAt(row - 1, col);
    }

    private int getAt(int row, int col) {
        if (row < 0 || col < 0 || col >= triangle[row].length) {
            return 0;
        }
        return triangle[row][col];
    }
}