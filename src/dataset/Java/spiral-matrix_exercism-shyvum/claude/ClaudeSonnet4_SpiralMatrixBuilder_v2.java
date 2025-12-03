class SpiralMatrixBuilder {
    public int[][] buildMatrixOfSize(int n) {
        int[][] result = new int[n][n];
        int cnt = 1;
        int top = 0, bottom = n - 1, left = 0, right = n - 1;
        
        while (top <= bottom && left <= right) {
            // Fill top row
            for (int col = left; col <= right; col++) {
                result[top][col] = cnt++;
            }
            top++;
            
            // Fill right column
            for (int row = top; row <= bottom; row++) {
                result[row][right] = cnt++;
            }
            right--;
            
            // Fill bottom row (if exists)
            if (top <= bottom) {
                for (int col = right; col >= left; col--) {
                    result[bottom][col] = cnt++;
                }
                bottom--;
            }
            
            // Fill left column (if exists)
            if (left <= right) {
                for (int row = bottom; row >= top; row--) {
                    result[row][left] = cnt++;
                }
                left++;
            }
        }
        
        return result;
    }
}