class PascalsTriangleGenerator {
    public static int[][] generateTriangle(int height) {
        if (height <= 0) {
            return new int[0][0];
        }

        int[][] triangle = new int[height][];
        triangle[0] = new int[]{1};

        for (int row = 1; row < height; row++) {
            triangle[row] = new int[row + 1];
            triangle[row][0] = 1;
            for (int col = 1; col < row; col++) {
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
            triangle[row][row] = 1;
        }

        return triangle;
    }
}