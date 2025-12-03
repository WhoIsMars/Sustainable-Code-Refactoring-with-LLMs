import java.util.Map;

class ResistorColorDuo {
    private static final Map<String, Integer> COLOR_CODE = Map.of(
            "black", 0, "brown", 1, "red", 2, "orange", 3, "yellow", 4,
            "green", 5, "blue", 6, "violet", 7, "grey", 8, "white", 9);

    int value(String[] colors) {
        return COLOR_CODE.get(colors[0]) * 10 + COLOR_CODE.get(colors[1]);
    }
}