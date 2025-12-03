import java.util.List;

class ResistorColorDuo {
    private static final List<String> colorCode = List.of(
            "black", "brown", "red", "orange", "yellow",
            "green", "blue", "violet", "grey", "white");

    int value(String[] colors) {
        return colorCode.indexOf(colors[0]) * 10 + colorCode.indexOf(colors[1]);
    }
}