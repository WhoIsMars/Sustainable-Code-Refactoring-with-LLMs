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
            for (int col = 0; col < cols; col++) {
                rowBuilder.append(findCellContent(row, col));
            }
            result.add(rowBuilder.toString());
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
        int count = 0;
        int startRow = Math.max(0, row - 1);
        int endRow = Math.min(rows - 1, row + 1);
        int startCol = Math.max(0, col - 1);
        int endCol = Math.min(cols - 1, col + 1);
        
        for (int r = startRow; r <= endRow; r++) {
            for (int c = startCol; c <= endCol; c++) {
                if (r != row || c != col) {
                    if (inputBoard.get(r).charAt(c) == '*') {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    private int lookAtNeighbourCell(int row, int col, int neighbourRow, int neighbourCol) {
        if (neighbourRow == row && neighbourCol == col) {
            return 0;
        }
        return isThereABombAt(neighbourRow, neighbourCol) ? 1 : 0;
    }

    private boolean isThereABombAt(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return false;
        }
        return inputBoard.get(row).charAt(col) == '*';
    }
}