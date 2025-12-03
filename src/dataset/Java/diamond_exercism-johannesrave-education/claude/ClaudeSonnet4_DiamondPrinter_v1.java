import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {
    
    public static List<String> printToList(char a) {
        int numLetters = a - 'A' + 1;
        int dim = numLetters * 2 - 1;
        List<String> diamond = new ArrayList<>(dim);
        
        // Build upper half (including middle)
        for (int i = 0; i < numLetters; i++) {
            char letter = (char)('A' + i);
            StringBuilder row = new StringBuilder(dim);
            
            // Left padding
            for (int j = 0; j < numLetters - 1 - i; j++) {
                row.append(' ');
            }
            
            // First letter
            row.append(letter);
            
            // Middle spacing (if not 'A')
            if (i > 0) {
                for (int j = 0; j < 2 * i - 1; j++) {
                    row.append(' ');
                }
                row.append(letter);
            }
            
            // Right padding
            while (row.length() < dim) {
                row.append(' ');
            }
            
            diamond.add(row.toString());
        }
        
        // Build lower half (mirror upper half excluding middle)
        for (int i = numLetters - 2; i >= 0; i--) {
            diamond.add(diamond.get(i));
        }
        
        return diamond;
    }
}