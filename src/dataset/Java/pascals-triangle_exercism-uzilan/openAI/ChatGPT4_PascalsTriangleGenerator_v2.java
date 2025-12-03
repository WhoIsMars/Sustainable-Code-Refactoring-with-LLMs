import java.util.ArrayList;
import java.util.List;

public class PascalsTriangleGenerator {

    public int[][] generateTriangle(int rows) {
        if (rows < 0) {
            throw new IllegalArgumentException("Number of rows may not be negative");
        }

        int[][] triangle = new int[rows][];
        for (int row = 0; row < rows; row++) {
            triangle[row] = new int[row + 1];
            triangle[row][0] = 1; // First element is always 1
            triangle[row][row] = 1; // Last element is always 1
            for (int col = 1; col < row; col++) {
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
        }
        return triangle;
    }
}