import java.util.List;

public class House {

    private static final String[] ROWS = (
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
            "that lay in the house that Jack built."
    ).split("\n");

    public String verse(int verse) {
        StringBuilder result = new StringBuilder("This is ");
        for (int i = ROWS.length - verse; i < ROWS.length; i++) {
            if (i == ROWS.length - verse) {
                int theIndex = ROWS[i].indexOf("the");
                result.append(ROWS[i], theIndex, ROWS[i].length()).append(" ");
            } else {
                result.append(ROWS[i]).append(" ");
            }
        }
        return result.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        StringBuilder result = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            if (i > startVerse) {
                result.append("\n");
            }
            result.append(verse(i));
        }
        return result.toString();
    }

    public String sing() {
        return verses(1, ROWS.length);
    }
}