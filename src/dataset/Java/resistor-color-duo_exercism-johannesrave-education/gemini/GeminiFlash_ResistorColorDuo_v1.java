import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

class ResistorColorDuo {
    private static final Map<String, Integer> colorCode = List.of(
            "black", "brown", "red", "orange", "yellow",
            "green", "blue", "violet", "grey", "white")
            .stream()
            .collect(Collectors.toMap(Function.identity(), List.of(
                    "black", "brown", "red", "orange", "yellow",
                    "green", "blue", "violet", "grey", "white")::indexOf));

    int value(String[] colors) {
        return colorCode.get(colors[0]) * 10 + colorCode.get(colors[1]);
    }
}