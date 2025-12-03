import java.util.List;
import java.util.stream.Collectors;

public class MinesweeperBoard {

    private final List<String> inputBoard;
    private final int rows;
    private final int cols;

    public MinesweeperBoard(List<String> inputBoard) {
        this.inputBoard = inputBoard;
        this.rows = inputBoard.size();
        this.cols = inputBoard.isEmpty() ? 0 : inputBoard.get(0).length();
    }

    public List<String> withNumbers() {
        return inputBoard.stream()
                .map(this::processRow)
                .collect(Collectors.toList());
    }

    private String processRow(String row) {
        StringBuilder result = new StringBuilder(cols);
        for (int col = 0; col < cols; col++) {
            result.append(findCellContent(inputBoard.indexOf(row), col));
        }
        return result.toString();
    }

    private String findCellContent(int row, int col) {
        if (isThereABombAt(row, col)) {
            return "*";
        }

        int bombCount = 0;
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if ((r != row || c != col) && isThereABombAt(r, c)) {
                    bombCount++;
                }
            }
        }
        return bombCount == 0 ? " " : Integer.toString(bombCount);
    }

    private boolean isThereABombAt(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols && inputBoard.get(row).charAt(col) == '*';
    }
}