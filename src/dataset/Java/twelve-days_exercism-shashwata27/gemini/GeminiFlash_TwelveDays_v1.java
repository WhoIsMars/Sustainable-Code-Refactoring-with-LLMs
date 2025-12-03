import java.util.List;
import java.util.Map;

class TwelveDays {
    private static final Map<Integer, String[]> days = Map.ofEntries(
            Map.entry(1, new String[]{"first", "and a Partridge in a Pear Tree."}),
            Map.entry(2, new String[]{"second", "two Turtle Doves"}),
            Map.entry(3, new String[]{"third", "three French Hens"}),
            Map.entry(4, new String[]{"fourth", "four Calling Birds"}),
            Map.entry(5, new String[]{"fifth", "five Gold Rings"}),
            Map.entry(6, new String[]{"sixth", "six Geese-a-Laying"}),
            Map.entry(7, new String[]{"seventh", "seven Swans-a-Swimming"}),
            Map.entry(8, new String[]{"eighth", "eight Maids-a-Milking"}),
            Map.entry(9, new String[]{"ninth", "nine Ladies Dancing"}),
            Map.entry(10, new String[]{"tenth", "ten Lords-a-Leaping"}),
            Map.entry(11, new String[]{"eleventh", "eleven Pipers Piping"}),
            Map.entry(12, new String[]{"twelfth", "twelve Drummers Drumming"}));

    String verse(int verseNumber) {
        StringBuilder verseText = new StringBuilder();
        verseText.append("On the ").append(days.get(verseNumber)[0]).append(" day of Christmas my true love gave to me: ");

        for (int i = verseNumber; i >= 1; i--) {
            verseText.append(days.get(i)[1]);
            if (i > 1) {
                verseText.append(", ");
            } else if (verseNumber > 1) {
                verseText.append(", ");
                verseText.append("and a Partridge in a Pear Tree.");
            }
        }
        verseText.append(".\n");
        return verseText.toString();
    }

    String verses(int startVerse, int endVerse) {
        StringBuilder versesText = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            versesText.append(verse(i));
            if (i != endVerse) {
                versesText.append("\n");
            }
        }
        return versesText.toString();
    }

    String sing() {
        return verses(1, 12);
    }
}