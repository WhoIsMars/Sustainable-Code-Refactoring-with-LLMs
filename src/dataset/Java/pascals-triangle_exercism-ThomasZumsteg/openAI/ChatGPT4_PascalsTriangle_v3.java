public class PascalsTriangle {
    public static int[][] computeTriangle(int rows) {
        if (rows < 0)
            throw new IllegalArgumentException();
        int[][] triangle = new int[rows][];
        for (int row = 0; row < rows; row++) {
            triangle[row] = new int[row + 1];
            triangle[row][0] = 1;
            triangle[row][row] = 1;
            for (int col = 1; col < row; col++) {
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
        }
        return triangle;
    }

    private static int binomial(int n, int k) {
        if (k == 0 || k == n) return 1;
        k = Math.min(k, n - k);
        long result = 1;
        for (int i = 1; i <= k; i++) {
            result = result * (n - i + 1) / i;
        }
        return (int) result;
    }

    public static boolean isTriangle(int[][] triangle) {
        for (int row = 0; row < triangle.length; row++) {
            if (triangle[row][0] != 1 || triangle[row][row] != 1)
                return false;
            for (int col = 1; col < row; col++) {
                if (triangle[row][col] != triangle[row - 1][col - 1] + triangle[row - 1][col])
                    return false;
            }
        }
        return true;
    }
}