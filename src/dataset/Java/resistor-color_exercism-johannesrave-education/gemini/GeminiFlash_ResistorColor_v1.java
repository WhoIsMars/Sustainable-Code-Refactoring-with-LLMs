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

    private static final java.util.Map<String, Integer> colorMap = new java.util.HashMap<>();

    static {
        for (int i = 0; i < COLORS.length; i++) {
            colorMap.put(COLORS[i], i);
        }
    }


    int colorCode(String color) {
        return colorMap.getOrDefault(color, -1);
    }

    String[] colors() {
        return COLORS.clone();
    }
}