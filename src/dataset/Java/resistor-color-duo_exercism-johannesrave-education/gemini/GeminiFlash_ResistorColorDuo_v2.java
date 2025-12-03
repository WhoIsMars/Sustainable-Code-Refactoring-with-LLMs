import java.util.Map;
import java.util.List;
import java.util.Collections;
import java.util.HashMap;

class ResistorColorDuo {
    private static final Map<String, Integer> colorCodeMap;

    static {
        Map<String, Integer> tempMap = new HashMap<>();
        tempMap.put("black", 0);
        tempMap.put("brown", 1);
        tempMap.put("red", 2);
        tempMap.put("orange", 3);
        tempMap.put("yellow", 4);
        tempMap.put("green", 5);
        tempMap.put("blue", 6);
        tempMap.put("violet", 7);
        tempMap.put("grey", 8);
        tempMap.put("white", 9);
        colorCodeMap = Collections.unmodifiableMap(tempMap);
    }

    int value(String[] colors) {
        return colorCodeMap.get(colors[0]) * 10 + colorCodeMap.get(colors[1]);
    }
}