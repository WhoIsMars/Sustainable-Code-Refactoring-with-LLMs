import java.util.HashMap;
import java.util.Map;

class ResistorColor {
    private static final Map<String, Integer> COLOR_MAP = Map.of(
        "black", 0,
        "brown", 1,
        "red", 2,
        "orange", 3,
        "yellow", 4,
        "green", 5,
        "blue", 6,
        "violet", 7,
        "grey", 8,
        "white", 9
    );
    
    private static final String[] COLOR_ARRAY = {
        "black", "brown", "red", "orange", "yellow",
        "green", "blue", "violet", "grey", "white"
    };
    
    int colorCode(String color) {
        return COLOR_MAP.get(color);
    }

    String[] colors() {
        return COLOR_ARRAY.clone();
    }
}