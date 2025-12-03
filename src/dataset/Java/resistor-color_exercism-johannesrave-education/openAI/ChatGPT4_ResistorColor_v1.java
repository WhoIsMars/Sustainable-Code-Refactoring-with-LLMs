import java.util.HashMap;
import java.util.Map;

class ResistorColor {
    static private final String[] COLORS = {
            "black", 
            "brown", 
            "red", 
            "orange", 
            "yellow", 
            "green", 
            "blue", 
            "violet", 
            "grey", 
            "white"};
    
    static private final Map<String, Integer> COLOR_MAP = new HashMap<>();
    
    static {
        for (int i = 0; i < COLORS.length; i++) {
            COLOR_MAP.put(COLORS[i], i);
        }
    }

    int colorCode(String color) {
        return COLOR_MAP.getOrDefault(color, -1);
    }

    String[] colors() {
        return COLORS;
    }
}