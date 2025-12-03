import java.util.Arrays;
import java.util.List;

public class FoodChain {

    private static final String[][] LYRICS = {
            {"fly", "I don't know why she swallowed the fly. Perhaps she'll die."},
            {"spider", "It wriggled and jiggled and tickled inside her."},
            {"bird", "How absurd to swallow a bird!"},
            {"cat", "Imagine that, to swallow a cat!"},
            {"dog", "What a hog, to swallow a dog!"},
            {"goat", "Just opened her throat and swallowed a goat!"},
            {"cow", "I don't know how she swallowed a cow!"},
            {"horse", "She's dead, of course!"}
    };

    public String verse(int verse) {
        final String[] row = LYRICS[verse - 1];
        final StringBuilder sb = new StringBuilder(128);
        
        sb.append("I know an old lady who swallowed a ").append(row[0])
          .append(".\n").append(row[1]).append("\n");

        if (verse < LYRICS.length) {
            helper(verse - 1, sb, row[0]);
        }

        return sb.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        final StringBuilder result = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            if (i > startVerse) {
                result.append("\n\n");
            }
            result.append(verse(i));
        }
        return result.toString();
    }

    private void helper(int verse, StringBuilder sb, String previous) {
        if (verse == 0) {
            return;
        }

        final String[] row = LYRICS[verse - 1];
        sb.append("She swallowed the ").append(previous).append(" to catch the ").append(row[0]);

        switch (verse) {
            case 1:
                sb.append(".\n").append(row[1]);
                break;
            case 2:
                sb.append(" that").append(row[1].substring(2)).append("\n");
                break;
            default:
                sb.append(".\n");
        }

        helper(verse - 1, sb, row[0]);
    }
}