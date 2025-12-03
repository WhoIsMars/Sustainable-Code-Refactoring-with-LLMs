import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class FoodChain {

    private static final List<String> LYRICS =
            Arrays.asList(
                    "fly#I don't know why she swallowed the fly. Perhaps she'll die.",
                    "spider#It wriggled and jiggled and tickled inside her.",
                    "bird#How absurd to swallow a bird!",
                    "cat#Imagine that, to swallow a cat!",
                    "dog#What a hog, to swallow a dog!",
                    "goat#Just opened her throat and swallowed a goat!",
                    "cow#I don't know how she swallowed a cow!",
                    "horse#She's dead, of course!");

    public String verse(int verse) {
        String[] row = LYRICS.get(verse - 1).split("#");
        StringBuilder sb = new StringBuilder();
        sb.append("I know an old lady who swallowed a ").append(row[0]).append(".\n").append(row[1]).append('\n');

        if (verse < LYRICS.size()) {
            buildVerse(verse - 1, sb, row[0]);
        }

        return sb.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        return IntStream.rangeClosed(startVerse, endVerse)
                .mapToObj(this::verse)
                .collect(Collectors.joining("\n\n"));
    }

    private void buildVerse(int verse, StringBuilder sb, String previous) {
        if (verse == 0) {
            return;
        }

        String[] row = LYRICS.get(verse - 1).split("#");
        sb.append("She swallowed the ").append(previous).append(" to catch the ").append(row[0]);

        switch (verse) {
            case 1:
                sb.append(".\n").append(row[1]);
                break;
            case 2:
                sb.append(" that wriggled and jiggled and tickled inside her.\n");
                break;
            default:
                sb.append(".\n");
        }

        buildVerse(verse - 1, sb, row[0]);
    }
}