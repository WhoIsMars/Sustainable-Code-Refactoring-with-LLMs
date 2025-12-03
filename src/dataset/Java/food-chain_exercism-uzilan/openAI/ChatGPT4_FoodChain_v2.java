import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class FoodChain {

    private static final List<String[]> LYRICS = Arrays.asList(
            new String[]{"fly", "I don't know why she swallowed the fly. Perhaps she'll die."},
            new String[]{"spider", "It wriggled and jiggled and tickled inside her."},
            new String[]{"bird", "How absurd to swallow a bird!"},
            new String[]{"cat", "Imagine that, to swallow a cat!"},
            new String[]{"dog", "What a hog, to swallow a dog!"},
            new String[]{"goat", "Just opened her throat and swallowed a goat!"},
            new String[]{"cow", "I don't know how she swallowed a cow!"},
            new String[]{"horse", "She's dead, of course!"}
    );

    public String verse(int verse) {
        StringBuilder sb = new StringBuilder();
        String[] current = LYRICS.get(verse - 1);

        sb.append("I know an old lady who swallowed a ").append(current[0]).append(".\n")
          .append(current[1]).append("\n");

        if (verse < LYRICS.size()) {
            appendHelper(verse - 1, sb, current[0]);
        }

        return sb.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        return IntStream.rangeClosed(startVerse, endVerse)
                .mapToObj(this::verse)
                .collect(Collectors.joining("\n\n"));
    }

    private void appendHelper(int verse, StringBuilder sb, String previous) {
        if (verse == 0) {
            return;
        }

        String[] current = LYRICS.get(verse - 1);
        sb.append("She swallowed the ").append(previous).append(" to catch the ").append(current[0]);

        if (verse == 1) {
            sb.append(".\n").append(current[1]);
        } else if (verse == 2) {
            sb.append(current[1].replace("It", " that")).append("\n");
        } else {
            sb.append(".\n");
        }

        appendHelper(verse - 1, sb, current[0]);
    }
}