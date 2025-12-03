import java.util.ArrayList;
import java.util.List;

public class PascalsTriangleGenerator {

    private List<List<Integer>> triangle;

    public int[][] generateTriangle(int rows) {
        if (rows < 0) {
            throw new IllegalArgumentException("Number of rows may not be negative");
        }

        triangle = new ArrayList<>(rows);
        for (int i = 0; i < rows; i++) {
            List<Integer> row = new ArrayList<>(i + 1);
            row.add(1);
            for (int j = 1; j < i; j++) {
                row.add(triangle.get(i - 1).get(j - 1) + triangle.get(i - 1).get(j));
            }
            if (i > 0) {
                row.add(1);
            }
            triangle.add(row);
        }
        return getTheTriangleAsDoubleArray();
    }

    private int[][] getTheTriangleAsDoubleArray() {
        int[][] result = new int[triangle.size()][];
        for (int i = 0; i < triangle.size(); i++) {
            List<Integer> row = triangle.get(i);
            result[i] = row.stream().mapToInt(Integer::intValue).toArray();
        }
        return result;
    }
}