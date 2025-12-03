import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {
    
    public static List<String> printToList(char a) {
        int n = a - 'A' + 1;
        List<String> diamond = new ArrayList<>(n * 2 - 1);
        
        // Top half including middle
        for (int i = 0; i < n; i++) {
            char letter = (char)('A' + i);
            StringBuilder sb = new StringBuilder(n * 2 - 1);
            
            // Left padding
            for (int j = 0; j < n - 1 - i; j++) {
                sb.append(' ');
            }
            
            // First letter
            sb.append(letter);
            
            // Middle spaces and second letter (if not 'A')
            if (i > 0) {
                for (int j = 0; j < 2 * i - 1; j++) {
                    sb.append(' ');
                }
                sb.append(letter);
            }
            
            // Right padding
            for (int j = 0; j < n - 1 - i; j++) {
                sb.append(' ');
            }
            
            diamond.add(sb.toString());
        }
        
        // Bottom half (mirror of top half excluding middle)
        for (int i = n - 2; i >= 0; i--) {
            diamond.add(diamond.get(i));
        }
        
        return diamond;
    }
}