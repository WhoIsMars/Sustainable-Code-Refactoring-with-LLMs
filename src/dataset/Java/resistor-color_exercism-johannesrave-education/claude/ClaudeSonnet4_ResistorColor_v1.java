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
    
    static private final Map<String, Integer> COLOR_MAP;
    
    static {
        COLOR_MAP = new HashMap<>(COLORS.length);
        for (int i = 0; i < COLORS.length; i++) {
            COLOR_MAP.put(COLORS[i], i);
        }
    }
    
    int colorCode(String color) {
        Integer code = COLOR_MAP.get(color);
        return code != null ? code : -1;
    }

    String[] colors() {
        return COLORS.clone();
    }
}