import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    List<String> printToList(char ch) {
        List<String> strings = new ArrayList<>();
        int size = ch - 'A' + 1;

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
        int innerSpaces = i == 0 ? 0 : 2 * i - 1;
        char c = (char) ('A' + i);

        StringBuilder line = new StringBuilder();
        appendSpaces(line, outerSpaces);
        line.append(c);
        if (innerSpaces > 0) {
            appendSpaces(line, innerSpaces);
            line.append(c);
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