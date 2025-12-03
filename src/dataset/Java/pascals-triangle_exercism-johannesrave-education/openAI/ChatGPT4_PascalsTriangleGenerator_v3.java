class PascalsTriangleGenerator {
    public static int[][] generateTriangle(int height) {
        if (height <= 0) return new int[0][];
        
        int[][] triangle = new int[height][];
        triangle[0] = new int[]{1};
        
        for (int row = 1; row < height; row++) {
            int[] currentRow = new int[row + 1];
            int[] previousRow = triangle[row - 1];
            currentRow[0] = currentRow[row] = 1;
            for (int col = 1; col < row; col++) {
                currentRow[col] = previousRow[col - 1] + previousRow[col];
            }
            triangle[row] = currentRow;
        }
        
        return triangle;
    }
}