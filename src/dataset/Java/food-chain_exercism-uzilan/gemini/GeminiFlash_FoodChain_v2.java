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

    private static final String NL = "\n";
    private static final String NL2 = "\n\n";
    private static final String SWALLOWED = "She swallowed the %s to catch the %s";
    private static final String I_KNOW = "I know an old lady who swallowed a %s.%s%s";


    public String verse(int verse) {
        String[] row = LYRICS.get(verse - 1).split("#");
        StringBuilder sb = new StringBuilder();
        sb.append(String.format(I_KNOW, row[0], NL, row[1]));
        sb.append(NL);

        if (verse < LYRICS.size()) {
            buildVerse(verse - 1, sb, row[0]);
        }

        return sb.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        return IntStream.rangeClosed(startVerse, endVerse)
                .mapToObj(this::verse)
                .collect(Collectors.joining(NL2));
    }

    private void buildVerse(int verse, StringBuilder sb, String previous) {
        if (verse == 0) {
            return;
        }

        String[] row = LYRICS.get(verse - 1).split("#");
        sb.append(String.format(SWALLOWED, previous, row[0]));

        switch (verse) {
            case 1:
                sb.append(".").append(NL).append(row[1]);
                break;
            case 2:
                sb.append(row[1].replace("It", " that")).append(NL);
                break;
            default:
                sb.append(".").append(NL);
        }

        buildVerse(verse - 1, sb, row[0]);
    }
}