import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    public static List<String> printToList(char a) {
        int size = (a - 'A') * 2 + 1;
        List<String> diamond = new ArrayList<>(size);

        for (int i = 0; i < size; i++) {
            char[] row = new char[size];
            int distance = Math.abs(size / 2 - i);
            char letter = (char) ('A' + distance);

            for (int j = 0; j < size; j++) {
                if (j == size / 2 - distance || j == size / 2 + distance) {
                    row[j] = letter;
                } else {
                    row[j] = ' ';
                }
            }
            diamond.add(new String(row));
        }

        return diamond;
    }
}