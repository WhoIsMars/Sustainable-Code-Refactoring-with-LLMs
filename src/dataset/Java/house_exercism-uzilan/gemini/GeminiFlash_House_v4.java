import java.util.Arrays;
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

    private static final List<String> ROWS = Arrays.asList(LYRICS.split("\n"));

    public String verse(int verse) {
        int end = ROWS.size();
        int start = end - verse;

        StringBuilder sb = new StringBuilder();
        for (int i = start; i < end; i++) {
            String row = ROWS.get(i);
            if (i == start) {
                int the = row.indexOf("the");
                sb.append("This is ").append(row.substring(the)).append(" ");
            } else {
                sb.append(row).append(" ");
            }
        }
        return sb.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        StringBuilder sb = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            sb.append(verse(i));
            if (i < endVerse) {
                sb.append("\n");
            }
        }
        return sb.toString();
    }

    public String sing() {
        return verses(1, ROWS.size());
    }
}