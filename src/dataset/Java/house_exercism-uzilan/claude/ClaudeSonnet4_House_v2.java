import java.util.Arrays;
import java.util.List;

public class House {

    private final String lyrics =
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

    private final String[] rows = lyrics.split("\n");

    public String verse(int verse) {
        final int end = rows.length;
        final int start = end - verse;
        
        StringBuilder sb = new StringBuilder();
        
        for (int i = start; i < end; i++) {
            final String row = rows[i];
            if (i == start) {
                final int the = row.indexOf("the");
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
            if (i > startVerse) {
                sb.append("\n");
            }
            sb.append(verse(i));
        }
        
        return sb.toString();
    }

    public String sing() {
        return verses(1, rows.length);
    }
}