import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    List<String> printToList(char ch) {
        int size = ch - 'A' + 1;
        List<String> strings = new ArrayList<>(size * 2 - 1);

        for (int i = 0; i < size; i++) {
            char currentChar = (char) ('A' + i);
            int outerSpaceCount = size - i - 1;
            StringBuilder sb = new StringBuilder();

            for (int j = 0; j < outerSpaceCount; j++) {
                sb.append(' ');
            }

            if (currentChar == 'A') {
                sb.append('A');
                for (int j = 0; j < outerSpaceCount; j++) {
                    sb.append(' ');
                }
            } else {
                sb.append(currentChar);
                int innerSpaceCount = 2 * i - 1;
                for (int j = 0; j < innerSpaceCount; j++) {
                    sb.append(' ');
                }
                sb.append(currentChar);
                for (int j = 0; j < outerSpaceCount; j++) {
                    sb.append(' ');
                }
            }
            strings.add(sb.toString());
        }

        for (int i = size - 2; i >= 0; i--) {
            strings.add(strings.get(i));
        }

        return strings;
    }
}