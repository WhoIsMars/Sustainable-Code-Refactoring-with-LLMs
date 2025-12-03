import java.util.ArrayList;
import java.util.List;

public class MinesweeperBoard {

    private final List<String> inputBoard;
    private final int rows;
    private final int cols;

    public MinesweeperBoard(List<String> inputBoard) {
        this.inputBoard = inputBoard;
        this.rows = inputBoard.size();
        this.cols = rows > 0 ? inputBoard.get(0).length() : 0;
    }

    public List<String> withNumbers() {
        List<String> result = new ArrayList<>(rows);
        
        for (int row = 0; row < rows; row++) {
            StringBuilder rowBuilder = new StringBuilder(cols);
            String currentRow = inputBoard.get(row);
            
            for (int col = 0; col < cols; col++) {
                if (currentRow.charAt(col) == '*') {
                    rowBuilder.append('*');
                } else {
                    int bombCount = countBombsAround(row, col);
                    rowBuilder.append(bombCount == 0 ? ' ' : (char)('0' + bombCount));
                }
            }
            result.add(rowBuilder.toString());
        }
        
        return result;
    }

    private int countBombsAround(int row, int col) {
        int count = 0;
        int startRow = Math.max(0, row - 1);
        int endRow = Math.min(rows - 1, row + 1);
        int startCol = Math.max(0, col - 1);
        int endCol = Math.min(cols - 1, col + 1);
        
        for (int r = startRow; r <= endRow; r++) {
            String currentRow = inputBoard.get(r);
            for (int c = startCol; c <= endCol; c++) {
                if ((r != row || c != col) && currentRow.charAt(c) == '*') {
                    count++;
                }
            }
        }
        
        return count;
    }
}