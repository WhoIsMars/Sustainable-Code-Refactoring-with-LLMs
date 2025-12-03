import java.util.Arrays;
import java.util.List;

public class House {

    private static final String[] ROWS = {
            "This is the horse and the hound and the horn",
            "that belonged to the farmer sowing his corn",
            "that kept the rooster that crowed in the morn",
            "that woke the priest all shaven and shorn",
            "that married the man all tattered and torn",
            "that kissed the maiden all forlorn",
            "that milked the cow with the crumpled horn",
            "that tossed the dog",
            "that worried the cat",
            "that killed the rat",
            "that ate the malt",
            "that lay in the house that Jack built."
    };

    private final List<String> rows = Arrays.asList(ROWS);

    public String verse(int verse) {
        final int end = ROWS.length;
        final int start = end - verse;
        
        StringBuilder result = new StringBuilder();
        
        for (int i = start; i < end; i++) {
            if (i == start) {
                result.append("This is ").append(ROWS[i].substring(12));
            } else {
                result.append(ROWS[i]);
            }
            result.append(' ');
        }
        
        return result.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        StringBuilder result = new StringBuilder();
        
        for (int i = startVerse; i <= endVerse; i++) {
            if (i > startVerse) {
                result.append('\n');
            }
            result.append(verse(i));
        }
        
        return result.toString();
    }

    public String sing() {
        return verses(1, ROWS.length);
    }
}