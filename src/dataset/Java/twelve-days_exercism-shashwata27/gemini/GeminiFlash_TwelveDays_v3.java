import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class TwelveDays {

    private static final Map<Integer, List<String>> DAYS = Map.ofEntries(
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
            Map.entry(12, List.of("twelfth", "twelve Drummers Drumming"))
    );

    private static final String FIRST_VERSE = "On the first day of Christmas my true love gave to me: a Partridge in a Pear Tree.\n";

    String verse(int verseNumber) {
        if (verseNumber == 1) {
            return FIRST_VERSE;
        }

        String gifts = IntStream.rangeClosed(1, verseNumber)
                .boxed()
                .sorted((a, b) -> Integer.compare(b, a))
                .map(i -> DAYS.get(i).get(1))
                .collect(Collectors.joining(", "));

        String prefix = "On the " + DAYS.get(verseNumber).get(0) + " day of Christmas my true love gave to me: ";
        if (verseNumber > 1) {
            gifts = gifts.substring(0, gifts.lastIndexOf(", ")) + ", and " + gifts.substring(gifts.lastIndexOf(", ") + 2);
        }
        return prefix + gifts + ".\n";
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