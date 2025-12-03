class PascalsTriangleGenerator{
    public static int[][] generateTriangle(int height){
        if (height <= 0) {
            return new int[0][];
        }
        
        int[][] triangle = new int[height][];
        
        for (int row = 0; row < height; row++) {
            triangle[row] = new int[row + 1];
            triangle[row][0] = 1;
            triangle[row][row] = 1;
            
            for (int col = 1; col < row; col++) {
                triangle[row][col] = triangle[row-1][col-1] + triangle[row-1][col];
            }
        }

        return triangle;
    }
}