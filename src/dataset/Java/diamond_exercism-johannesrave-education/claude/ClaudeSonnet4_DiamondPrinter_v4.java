import java.util.ArrayList;
import java.util.List;

class DiamondPrinter {
    
    public static List<String> printToList(char a) {
        if (a == 'A') {
            List<String> result = new ArrayList<>(1);
            result.add("A");
            return result;
        }
        
        int letterIndex = a - 'A';
        int dim = letterIndex * 2 + 1;
        int center = letterIndex;
        
        List<String> diamond = new ArrayList<>(dim);
        
        for (int row = 0; row < dim; row++) {
            char[] line = new char[dim];
            java.util.Arrays.fill(line, ' ');
            
            int distanceFromCenter = Math.abs(row - center);
            char currentLetter = (char) ('A' + center - distanceFromCenter);
            int letterPosition = distanceFromCenter;
            
            line[letterPosition] = currentLetter;
            if (letterPosition != center) {
                line[dim - letterPosition - 1] = currentLetter;
            }
            
            diamond.add(new String(line));
        }
        
        return diamond;
    }
}