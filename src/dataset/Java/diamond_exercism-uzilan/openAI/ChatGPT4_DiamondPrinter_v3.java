import java.util.ArrayList;
import java.util.List;

import static java.lang.String.format;

class DiamondPrinter {

    List<String> printToList(char ch) {
        int size = ch - 'A' + 1;
        List<String> strings = new ArrayList<>(2 * size - 1);

        for (int i = 0; i < size; i++) {
            strings.add(buildLine(ch, i));
        }

        for (int i = size - 2; i >= 0; i--) {
            strings.add(strings.get(i));
        }

        return strings;
    }

    private String buildLine(char ch, int i) {
        int outerSpaces = ch - ('A' + i);
        int innerSpaces = 2 * i - 1;

        StringBuilder line = new StringBuilder();
        appendSpaces(line, outerSpaces);
        line.append((char) ('A' + i));
        if (i > 0) {
            appendSpaces(line, innerSpaces);
            line.append((char) ('A' + i));
        }
        appendSpaces(line, outerSpaces);

        return line.toString();
    }

    private void appendSpaces(StringBuilder sb, int count) {
        for (int i = 0; i < count; i++) {
            sb.append(' ');
        }
    }
}