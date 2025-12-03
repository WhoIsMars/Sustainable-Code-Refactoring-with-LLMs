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

    private static final java.util.Map<String, Integer> COLOR_MAP = new java.util.HashMap<>();

    static {
        for (int i = 0; i < COLORS.length; i++) {
            COLOR_MAP.put(COLORS[i], i);
        }
    }


    int colorCode(String color) {
        return COLOR_MAP.getOrDefault(color, -1);
    }

    String[] colors() {
        return COLORS.clone();
    }
}