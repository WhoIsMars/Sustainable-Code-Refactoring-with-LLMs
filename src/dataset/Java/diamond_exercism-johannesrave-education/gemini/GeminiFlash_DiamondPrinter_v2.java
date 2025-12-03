import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    public static List<String> printToList(char a) {
        int dim = (a - 'A') * 2 + 1;
        List<String> diamond = new ArrayList<>(dim);
        char[] rowChars = new char[dim];

        for (int i = 0; i < dim; i++) {
            rowChars[i] = ' ';
        }

        for (int i = 0; i < dim / 2 + 1; i++) {
            char letter = (char) ('A' + i);
            int middle = dim / 2;
            rowChars[middle - i] = letter;
            rowChars[middle + i] = letter;

            diamond.add(new String(rowChars));

            if (i < dim / 2) {
                diamond.add(new String(rowChars));
            }

            rowChars[middle - i] = ' ';
            rowChars[middle + i] = ' ';
        }

        List<String> result = new ArrayList<>(dim);
        for (int i = 0; i < dim / 2; i++) {
            result.add(diamond.get(i));
        }
        for (int i = dim / 2; i < dim; i++) {
            result.add(diamond.get(dim - 1 - i + dim / 2));
        }

        return result;
    }
}