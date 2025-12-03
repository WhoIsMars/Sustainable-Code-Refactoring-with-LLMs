public class PascalsTriangle {
    public static int[][] computeTriangle(int rows) {
        if (rows < 0) {
            throw new IllegalArgumentException();
        }

        int[][] triangle = new int[rows][];

        for (int i = 0; i < rows; i++) {
            triangle[i] = new int[i + 1];
            triangle[i][0] = 1;
            triangle[i][i] = 1;

            for (int j = 1; j < i; j++) {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }

        return triangle;
    }

    public static boolean isTriangle(int[][] triangle) {
        for (int i = 0; i < triangle.length; i++) {
            if (triangle[i].length != i + 1) {
                return false;
            }
            if (triangle[i][0] != 1 || triangle[i][i] != 1) {
                return false;
            }
            for (int j = 1; j < i; j++) {
                if (triangle[i][j] != triangle[i - 1][j - 1] + triangle[i - 1][j]) {
                    return false;
                }
            }
        }
        return true;
    }
}