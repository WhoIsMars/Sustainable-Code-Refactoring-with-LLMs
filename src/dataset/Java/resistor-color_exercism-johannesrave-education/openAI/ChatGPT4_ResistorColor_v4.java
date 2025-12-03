import java.util.Map;
import java.util.HashMap;

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
    
    static private final Map<String, Integer> COLOR_MAP = createColorMap();

    private static Map<String, Integer> createColorMap() {
        Map<String, Integer> map = new HashMap<>();
        for (int i = 0; i < COLORS.length; i++) {
            map.put(COLORS[i], i);
        }
        return map;
    }

    int colorCode(String color) {
        return COLOR_MAP.getOrDefault(color, -1);
    }

    String[] colors() {
        return COLORS.clone();
    }
}