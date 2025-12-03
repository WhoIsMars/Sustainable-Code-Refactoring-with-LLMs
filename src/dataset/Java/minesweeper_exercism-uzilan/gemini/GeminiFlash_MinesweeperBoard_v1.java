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
            StringBuilder sb = new StringBuilder(cols);
            for (int col = 0; col < cols; col++) {
                sb.append(findCellContent(row, col));
            }
            result.add(sb.toString());
        }
        return result;
    }

    private String findCellContent(int row, int col) {
        if (isThereABombAt(row, col)) {
            return "*";
        }

        int bombCount = lookAround(row, col);
        return bombCount == 0 ? " " : Integer.toString(bombCount);
    }

    private int lookAround(int row, int col) {
        int bombCount = 0;
        for (int neighbourRow = Math.max(0, row - 1); neighbourRow <= Math.min(rows - 1, row + 1); neighbourRow++) {
            for (int neighbourCol = Math.max(0, col - 1); neighbourCol <= Math.min(cols - 1, col + 1); neighbourCol++) {
                if (neighbourRow == row && neighbourCol == col) {
                    continue;
                }
                if (isThereABombAt(neighbourRow, neighbourCol)) {
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
        return inputBoard.get(row).charAt(col) == '*';
    }
}