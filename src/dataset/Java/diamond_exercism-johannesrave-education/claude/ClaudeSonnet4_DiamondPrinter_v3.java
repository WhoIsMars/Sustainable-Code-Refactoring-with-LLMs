import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {
    
    public static List<String> printToList(char a) {
        int dim = (a - 'A') * 2 + 1;
        int center = dim / 2;
        List<String> diamond = new ArrayList<>(dim);
        
        for (int row = 0; row < dim; row++) {
            char[] line = new char[dim];
            int distanceFromCenter = Math.abs(row - center);
            char letter = (char) ('A' + distanceFromCenter);
            int letterPos = center - distanceFromCenter;
            
            for (int col = 0; col < dim; col++) {
                if (col == letterPos || col == dim - letterPos - 1) {
                    line[col] = letter;
                } else {
                    line[col] = ' ';
                }
            }
            
            diamond.add(new String(line));
        }
        
        return diamond;
    }
}