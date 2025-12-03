import java.util.ArrayList;
import java.util.List;

public class MinesweeperBoard {

    private final char[][] board;
    private final int rows;
    private final int cols;

    public MinesweeperBoard(List<String> inputBoard) {
        this.rows = inputBoard.size();
        this.cols = rows > 0 ? inputBoard.get(0).length() : 0;
        this.board = new char[rows][cols];
        
        for (int i = 0; i < rows; i++) {
            inputBoard.get(i).getChars(0, cols, board[i], 0);
        }
    }

    public List<String> withNumbers() {
        List<String> result = new ArrayList<>(rows);
        char[] rowBuffer = new char[cols];
        
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                rowBuffer[col] = findCellContent(row, col);
            }
            result.add(new String(rowBuffer));
        }
        
        return result;
    }

    private char findCellContent(int row, int col) {
        if (board[row][col] == '*') {
            return '*';
        }

        int bombCount = lookAround(row, col);
        return bombCount == 0 ? ' ' : (char)('0' + bombCount);
    }

    private int lookAround(int row, int col) {
        int count = 0;
        int startRow = Math.max(0, row - 1);
        int endRow = Math.min(rows - 1, row + 1);
        int startCol = Math.max(0, col - 1);
        int endCol = Math.min(cols - 1, col + 1);
        
        for (int r = startRow; r <= endRow; r++) {
            for (int c = startCol; c <= endCol; c++) {
                if (r != row || c != col) {
                    if (board[r][c] == '*') {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
}