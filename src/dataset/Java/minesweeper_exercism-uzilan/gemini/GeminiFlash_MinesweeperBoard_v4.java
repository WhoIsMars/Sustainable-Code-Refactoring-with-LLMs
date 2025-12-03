import java.util.ArrayList;
import java.util.List;

public class MinesweeperBoard {

    private final List<String> inputBoard;
    private final int rows;
    private final int cols;
    private final char[][] board;

    public MinesweeperBoard(List<String> inputBoard) {
        this.inputBoard = inputBoard;
        this.rows = inputBoard.size();
        this.cols = rows > 0 ? inputBoard.get(0).length() : 0;
        this.board = new char[rows][cols];
        for (int i = 0; i < rows; i++) {
            board[i] = inputBoard.get(i).toCharArray();
        }
    }

    public List<String> withNumbers() {
        List<String> result = new ArrayList<>(rows);
        for (int i = 0; i < rows; i++) {
            StringBuilder sb = new StringBuilder(cols);
            for (int j = 0; j < cols; j++) {
                sb.append(findCellContent(i, j));
            }
            result.add(sb.toString());
        }
        return result;
    }

    private char findCellContent(int row, int col) {
        if (isThereABombAt(row, col)) {
            return '*';
        }

        int bombCount = lookAround(row, col);
        return bombCount == 0 ? ' ' : (char) (bombCount + '0');
    }

    private int lookAround(int row, int col) {
        int bombCount = 0;
        for (int i = Math.max(0, row - 1); i <= Math.min(rows - 1, row + 1); i++) {
            for (int j = Math.max(0, col - 1); j <= Math.min(cols - 1, col + 1); j++) {
                if (i == row && j == col) {
                    continue;
                }
                if (isThereABombAt(i, j)) {
                    bombCount++;
                }
            }
        }
        return bombCount;
    }

    private boolean isThereABombAt(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return false;
        }
        return board[row][col] == '*';
    }
}