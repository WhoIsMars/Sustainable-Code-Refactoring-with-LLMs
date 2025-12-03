class PascalsTriangleGenerator {
    public static int[][] generateTriangle(int height) {
        int[][] triangle = new int[height][];
        for (int row = 0; row < height; row++) {
            int[] currentRow = new int[row + 1];
            currentRow[0] = 1;
            currentRow[row] = 1;
            for (int col = 1; col < row; col++) {
                currentRow[col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
            triangle[row] = currentRow;
        }
        return triangle;
    }
}