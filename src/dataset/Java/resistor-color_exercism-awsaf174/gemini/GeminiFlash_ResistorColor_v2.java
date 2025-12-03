import java.util.HashMap;
import java.util.Map;

class ResistorColor {

    private static final Map<String, Integer> colorCodeMap = new HashMap<>();
    private static final String[] colorArray = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "grey", "white"};

    static {
        colorCodeMap.put("black", 0);
        colorCodeMap.put("brown", 1);
        colorCodeMap.put("red", 2);
        colorCodeMap.put("orange", 3);
        colorCodeMap.put("yellow", 4);
        colorCodeMap.put("green", 5);
        colorCodeMap.put("blue", 6);
        colorCodeMap.put("violet", 7);
        colorCodeMap.put("grey", 8);
        colorCodeMap.put("white", 9);
    }

    int colorCode(String color) {
        return colorCodeMap.get(color);
    }

    String[] colors() {
        return colorArray.clone();
    }
}