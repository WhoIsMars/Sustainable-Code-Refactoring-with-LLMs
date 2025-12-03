import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    public static List<String> printToList(char a) {
        int dim = (a - 'A') * 2 + 1;
        List<String> diamond = new ArrayList<>(dim);

        for (int i = 0; i < dim; i++) {
            char[] row = new char[dim];
            java.util.Arrays.fill(row, ' ');
            diamond.add(new String(row));
        }

        for (char letter = 'A'; letter <= a; letter++) {
            int row = letter - 'A';
            int col = dim / 2 - row;

            String currentRow = diamond.get(row);
            char[] currentRowChars = currentRow.toCharArray();
            currentRowChars[col] = letter;
            currentRowChars[dim - col - 1] = letter;
            diamond.set(row, new String(currentRowChars));

            if (row != dim / 2) {
                String mirroredRow = diamond.get(dim - row - 1);
                char[] mirroredRowChars = mirroredRow.toCharArray();
                mirroredRowChars[col] = letter;
                mirroredRowChars[dim - col - 1] = letter;
                diamond.set(dim - row - 1, new String(mirroredRowChars));
            }
        }

        return diamond;
    }
}