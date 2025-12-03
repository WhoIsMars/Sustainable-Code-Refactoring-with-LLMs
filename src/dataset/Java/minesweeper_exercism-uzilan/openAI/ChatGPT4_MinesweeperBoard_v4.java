import java.util.List;
import java.util.ArrayList;

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

    private char findCellContent(int row, int col) {
        if (isThereABombAt(row, col)) {
            return '*';
        }
        int bombCount = 0;
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if ((r != row || c != col) && isThereABombAt(r, c)) {
                    bombCount++;
                }
            }
        }
        return bombCount == 0 ? ' ' : (char) ('0' + bombCount);
    }

    private boolean isThereABombAt(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols && inputBoard.get(row).charAt(col) == '*';
    }
}