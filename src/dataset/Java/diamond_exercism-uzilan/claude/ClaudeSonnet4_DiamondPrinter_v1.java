import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    List<String> printToList(char ch) {
        final int size = ch - 'A' + 1;
        final List<String> strings = new ArrayList<>(2 * size - 1);
        
        // Build upper half including middle
        for (int i = 0; i < size; i++) {
            final char c = (char) ('A' + i);
            final int outerSpaces = size - 1 - i;
            
            if (i == 0) {
                strings.add(buildString(outerSpaces, 'A', 0, outerSpaces));
            } else {
                final int innerSpaces = 2 * i - 1;
                strings.add(buildString(outerSpaces, c, innerSpaces, outerSpaces));
            }
        }
        
        // Build lower half (reverse of upper half excluding middle)
        for (int i = size - 2; i >= 0; i--) {
            strings.add(strings.get(i));
        }
        
        return strings;
    }

    private String buildString(int outerSpaces, char c, int innerSpaces, int trailingSpaces) {
        final StringBuilder sb = new StringBuilder();
        
        // Add outer spaces
        for (int i = 0; i < outerSpaces; i++) {
            sb.append(' ');
        }
        
        // Add first character
        sb.append(c);
        
        // Add inner spaces and second character (if not 'A')
        if (c != 'A') {
            for (int i = 0; i < innerSpaces; i++) {
                sb.append(' ');
            }
            sb.append(c);
        }
        
        // Add trailing spaces
        for (int i = 0; i < trailingSpaces; i++) {
            sb.append(' ');
        }
        
        return sb.toString();
    }
}