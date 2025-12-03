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

    private static final int TOTAL_VERSES = ROWS.length;

    public String verse(int verse) {
        final int start = TOTAL_VERSES - verse;
        final StringBuilder sb = new StringBuilder();
        
        for (int i = start; i < TOTAL_VERSES; i++) {
            if (i == start) {
                sb.append("This is ").append(ROWS[i].substring(12));
            } else {
                sb.append(ROWS[i]);
            }
            sb.append(' ');
        }
        
        return sb.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        final StringBuilder sb = new StringBuilder();
        
        for (int i = startVerse; i <= endVerse; i++) {
            if (i > startVerse) {
                sb.append('\n');
            }
            sb.append(verse(i));
        }
        
        return sb.toString();
    }

    public String sing() {
        return verses(1, TOTAL_VERSES);
    }
}