import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    public static List<String> printToList(char a) {
        int dim = (a - 'A') * 2 + 1;
        List<String> diamond = new ArrayList<>(dim);
        char[] row = new char[dim];

        for (int i = 0; i < dim; i++) {
            row[i] = ' ';
        }

        for (char letter = 'A'; letter <= a; letter++) {
            int rowIdx = letter - 'A';
            row[dim / 2 - rowIdx] = letter;
            row[dim / 2 + rowIdx] = letter;
            diamond.add(new String(row));
        }

        for (int i = dim / 2 - 1; i >= 0; i--) {
            diamond.add(diamond.get(i));
        }

        return diamond;
    }
}