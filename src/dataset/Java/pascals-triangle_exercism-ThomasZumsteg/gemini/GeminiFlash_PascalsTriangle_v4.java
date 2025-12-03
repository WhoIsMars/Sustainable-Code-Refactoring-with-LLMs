public class PascalsTriangle {
    public static int[][] computeTriangle(int rows) {
        if (rows < 0) {
            throw new IllegalArgumentException();
        }

        int[][] triangle = new int[rows][];

        for (int row = 0; row < rows; row++) {
            triangle[row] = new int[row + 1];
            triangle[row][0] = 1;
            for (int col = 1; col < row; col++) {
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
            if (row > 0) {
                triangle[row][row] = 1;
            }
        }

        return triangle;
    }

    public static boolean isTriangle(int[][] triangle) {
        if (triangle == null || triangle.length == 0) {
            return true;
        }

        for (int row = 0; row < triangle.length; row++) {
            if (triangle[row] == null || triangle[row].length != row + 1) {
                return false;
            }
            if (row == 0 && (triangle[row].length != 1 || triangle[row][0] != 1)) {
                return false;
            }
            if (row > 0) {
                if (triangle[row][0] != 1 || triangle[row][row] != 1) {
                    return false;
                }
                for (int col = 1; col < row; col++) {
                    if (triangle[row][col] != triangle[row - 1][col - 1] + triangle[row - 1][col]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
}