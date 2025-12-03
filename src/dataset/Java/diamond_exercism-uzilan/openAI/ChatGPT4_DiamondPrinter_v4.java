import java.util.ArrayList;
import java.util.List;

import static java.lang.String.format;

class DiamondPrinter {

    List<String> printToList(char ch) {
        int size = ch - 'A' + 1;
        List<String> strings = new ArrayList<>(2 * size - 1);

        for (int i = 0; i < size; i++) {
            strings.add(buildLine(ch, (char) ('A' + i), i));
        }

        for (int i = size - 2; i >= 0; i--) {
            strings.add(strings.get(i));
        }

        return strings;
    }

    private String buildLine(char ch, char currentChar, int index) {
        int outerSpaces = ch - currentChar;
        if (currentChar == 'A') {
            return " ".repeat(outerSpaces) + "A" + " ".repeat(outerSpaces);
        }
        int innerSpaces = 2 * index - 1;
        return " ".repeat(outerSpaces) + currentChar + " ".repeat(innerSpaces) + currentChar + " ".repeat(outerSpaces);
    }
}