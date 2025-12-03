import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {

    List<String> printToList(char ch) {
        int size = ch - 'A' + 1;
        List<String> result = new ArrayList<>(2 * size - 1);
        
        // Build upper half including middle
        for (int i = 0; i < size; i++) {
            char c = (char) ('A' + i);
            int outerSpaces = size - 1 - i;
            
            if (i == 0) {
                result.add(buildString(outerSpaces, 'A', 0, outerSpaces));
            } else {
                int innerSpaces = 2 * i - 1;
                result.add(buildString(outerSpaces, c, innerSpaces, outerSpaces));
            }
        }
        
        // Build lower half (reverse of upper half excluding middle)
        for (int i = size - 2; i >= 0; i--) {
            result.add(result.get(i));
        }
        
        return result;
    }

    private String buildString(int outerSpaces, char c, int innerSpaces, int trailingSpaces) {
        StringBuilder sb = new StringBuilder();
        
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