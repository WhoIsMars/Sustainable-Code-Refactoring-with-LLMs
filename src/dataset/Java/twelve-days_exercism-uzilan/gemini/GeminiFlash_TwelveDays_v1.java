import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class TwelveDays {

    private static final List<String> DAYS = Arrays.asList(
            "first",
            "second",
            "third",
            "fourth",
            "fifth",
            "sixth",
            "seventh",
            "eighth",
            "ninth",
            "tenth",
            "eleventh",
            "twelfth");

    private static final List<String> GIFTS = Arrays.asList(
            "a Partridge in a Pear Tree.",
            "two Turtle Doves, ",
            "three French Hens, ",
            "four Calling Birds, ",
            "five Gold Rings, ",
            "six Geese-a-Laying, ",
            "seven Swans-a-Swimming, ",
            "eight Maids-a-Milking, ",
            "nine Ladies Dancing, ",
            "ten Lords-a-Leaping, ",
            "eleven Pipers Piping, ",
            "twelve Drummers Drumming, ");

    String verse(int verseNumber) {
        final String day = DAYS.get(verseNumber - 1);
        final StringBuilder sb = new StringBuilder("On the " + day + " day of Christmas my true love gave to me, ");

        for (int i = verseNumber - 1; i > 0; i--) {
            sb.append(GIFTS.get(i));
        }

        if (verseNumber > 1) {
            sb.append("and ");
        }

        sb.append(GIFTS.get(0)).append("\n");

        return sb.toString();
    }

    String verses(int startVerse, int endVerse) {
        StringBuilder versesBuilder = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            versesBuilder.append(verse(i));
            if (i < endVerse) {
                versesBuilder.append("\n");
            }
        }
        return versesBuilder.toString();
    }

    String sing() {
        return verses(1, DAYS.size());
    }
}