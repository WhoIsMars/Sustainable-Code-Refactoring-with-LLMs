import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    public static List<String> printToList(char a) {
        int dim = (a - 'A') * 2 + 1;
        List<String> diamond = new ArrayList<>(dim);
        char[] rowBuffer = new char[dim];

        for (int i = 0; i < dim; i++) {
            rowBuffer[i] = ' ';
        }

        for (char letter = 'A'; letter <= a; letter++) {
            int row = letter - 'A';
            int col = dim / 2 - row;

            rowBuffer[col] = letter;
            rowBuffer[dim - col - 1] = letter;

            diamond.add(new String(rowBuffer));
        }

        for (int i = a - 'A' - 1; i >= 0; i--) {
            diamond.add(diamond.get(i));
        }

        return diamond;
    }
}