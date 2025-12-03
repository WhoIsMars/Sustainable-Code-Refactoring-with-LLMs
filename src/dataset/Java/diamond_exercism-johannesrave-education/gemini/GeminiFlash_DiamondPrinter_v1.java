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
            StringBuilder rowBuilder = new StringBuilder(currentRow);
            rowBuilder.setCharAt(col, letter);
            rowBuilder.setCharAt(dim - col - 1, letter);
            diamond.set(row, rowBuilder.toString());

            if (row != dim / 2) {
                String mirroredRow = diamond.get(dim - row - 1);
                StringBuilder mirroredRowBuilder = new StringBuilder(mirroredRow);
                mirroredRowBuilder.setCharAt(col, letter);
                mirroredRowBuilder.setCharAt(dim - col - 1, letter);
                diamond.set(dim - row - 1, mirroredRowBuilder.toString());
            }
        }

        return diamond;
    }
}