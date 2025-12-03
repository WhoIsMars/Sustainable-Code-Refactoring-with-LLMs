import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class House {

    private static final String LYRICS =
            "This is the horse and the hound and the horn\n" +
                    "that belonged to the farmer sowing his corn\n" +
                    "that kept the rooster that crowed in the morn\n" +
                    "that woke the priest all shaven and shorn\n" +
                    "that married the man all tattered and torn\n" +
                    "that kissed the maiden all forlorn\n" +
                    "that milked the cow with the crumpled horn\n" +
                    "that tossed the dog\n" +
                    "that worried the cat\n" +
                    "that killed the rat\n" +
                    "that ate the malt\n" +
                    "that lay in the house that Jack built.";

    private static final List<String> ROWS = List.of(LYRICS.split("\n"));

    public String verse(int verse) {
        int start = ROWS.size() - verse;
        StringBuilder result = new StringBuilder("This is ");
        for (int i = start; i < ROWS.size(); i++) {
            if (i == start) {
                int theIndex = ROWS.get(i).indexOf("the");
                result.append(ROWS.get(i).substring(theIndex)).append(" ");
            } else {
                result.append(ROWS.get(i)).append(" ");
            }
        }
        return result.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        return IntStream.rangeClosed(startVerse, endVerse)
                .mapToObj(this::verse)
                .collect(Collectors.joining("\n"));
    }

    public String sing() {
        return LYRICS;
    }
}