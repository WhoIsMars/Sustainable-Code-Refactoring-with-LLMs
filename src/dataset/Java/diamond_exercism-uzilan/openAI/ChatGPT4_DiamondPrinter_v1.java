import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    List<String> printToList(char ch) {
        List<String> strings = new ArrayList<>();
        int size = ch - 'A' + 1;

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
        int innerSpaces = index == 0 ? 0 : 2 * index - 1;

        StringBuilder line = new StringBuilder();
        appendSpaces(line, outerSpaces);
        line.append(currentChar);
        if (innerSpaces > 0) {
            appendSpaces(line, innerSpaces);
            line.append(currentChar);
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