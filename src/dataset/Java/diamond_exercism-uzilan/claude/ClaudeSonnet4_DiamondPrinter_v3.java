import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    List<String> printToList(char ch) {
        final int size = ch - 'A' + 1;
        final List<String> result = new ArrayList<>(2 * size - 1);
        
        // Build upper half including middle
        for (int i = 0; i < size; i++) {
            final char c = (char) ('A' + i);
            final int outerSpaces = size - 1 - i;
            
            if (i == 0) {
                result.add(buildString(outerSpaces, 'A', 0, outerSpaces));
            } else {
                final int innerSpaces = 2 * i - 1;
                result.add(buildString(outerSpaces, c, innerSpaces, outerSpaces));
            }
        }
        
        // Build lower half by reusing upper half strings
        for (int i = size - 2; i >= 0; i--) {
            result.add(result.get(i));
        }
        
        return result;
    }

    private String buildString(int outerSpaces, char c, int innerSpaces, int trailingSpaces) {
        final StringBuilder sb = new StringBuilder();
        
        // Outer spaces
        for (int i = 0; i < outerSpaces; i++) {
            sb.append(' ');
        }
        
        // First character
        sb.append(c);
        
        // Inner spaces and second character (if needed)
        if (innerSpaces > 0) {
            for (int i = 0; i < innerSpaces; i++) {
                sb.append(' ');
            }
            sb.append(c);
        }
        
        // Trailing spaces
        for (int i = 0; i < trailingSpaces; i++) {
            sb.append(' ');
        }
        
        return sb.toString();
    }

    private String spaceTimesX(int count) {
        if (count <= 0) return "";
        final StringBuilder sb = new StringBuilder(count);
        for (int i = 0; i < count; i++) {
            sb.append(' ');
        }
        return sb.toString();
    }
}