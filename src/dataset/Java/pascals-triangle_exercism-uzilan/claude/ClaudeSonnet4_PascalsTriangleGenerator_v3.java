import java.util.List;
import java.util.ArrayList;

public class PascalsTriangleGenerator {

    private int[][] triangle;

    public int[][] generateTriangle(int rows) {
        if (rows < 0) {
            throw new IllegalArgumentException("Number of rows may not be negative");
        }

        createTheTriangel(rows);
        manipulateTriangleValues(rows);
        return getTheTriangleAsDoubleArray();
    }

    private void createTheTriangel(int rows) {
        triangle = new int[rows][];
        for (int i = 0; i < rows; i++) {
            triangle[i] = new int[i + 1];
            triangle[i][0] = 1;
            if (i > 0) {
                triangle[i][i] = 1;
            }
        }
    }

    private void manipulateTriangleValues(int rows) {
        for (int row = 2; row < rows; row++) {
            for (int col = 1; col < row; col++) {
                recalculateCellValue(row, col);
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
        return triangle[row - 1][col - 1] + triangle[row - 1][col];
    }

    private int getAt(int row, int col) {
        if (row < 0 || col < 0 || row >= triangle.length || col >= triangle[row].length) {
            return 0;
        }
        return triangle[row][col];
    }
}