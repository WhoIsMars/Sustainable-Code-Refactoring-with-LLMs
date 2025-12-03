import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class TwelveDays {
    private static final Map<Integer, List<String>> days = Map.ofEntries(
            Map.entry(1, List.of("first", "a Partridge in a Pear Tree")),
            Map.entry(2, List.of("second", "two Turtle Doves")),
            Map.entry(3, List.of("third", "three French Hens")),
            Map.entry(4, List.of("fourth", "four Calling Birds")),
            Map.entry(5, List.of("fifth", "five Gold Rings")),
            Map.entry(6, List.of("sixth", "six Geese-a-Laying")),
            Map.entry(7, List.of("seventh", "seven Swans-a-Swimming")),
            Map.entry(8, List.of("eighth", "eight Maids-a-Milking")),
            Map.entry(9, List.of("ninth", "nine Ladies Dancing")),
            Map.entry(10, List.of("tenth", "ten Lords-a-Leaping")),
            Map.entry(11, List.of("eleventh", "eleven Pipers Piping")),
            Map.entry(12, List.of("twelfth", "twelve Drummers Drumming")));

    String verse(int verseNumber) {
        StringBuilder verse = new StringBuilder();
        verse.append("On the ").append(days.get(verseNumber).get(0)).append(" day of Christmas my true love gave to me: ");

        for (int i = verseNumber; i >= 1; i--) {
            verse.append(days.get(i).get(1));
            if (i > 1) {
                verse.append(", ");
            } else if (verseNumber > 1) {
                verse.append(", and ");
            }
        }
        verse.append(".\n");
        return verse.toString();
    }

    String verses(int startVerse, int endVerse) {
        return IntStream.rangeClosed(startVerse, endVerse)
                .mapToObj(this::verse)
                .collect(Collectors.joining("\n"));
    }

    String sing() {
        return verses(1, 12);
    }
}