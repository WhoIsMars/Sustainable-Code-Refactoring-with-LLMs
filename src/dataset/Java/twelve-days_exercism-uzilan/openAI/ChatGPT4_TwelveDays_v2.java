import java.util.List;

class TwelveDays {

    String verse(int verseNumber) {
        StringBuilder sb = new StringBuilder("On the ")
                .append(days[verseNumber - 1])
                .append(" day of Christmas my true love gave to me, ");

        for (int i = verseNumber - 1; i > 0; i--) {
            sb.append(gifts[i]);
        }

        if (verseNumber > 1) {
            sb.append("and ");
        }

        sb.append(gifts[0]).append("\n");

        return sb.toString();
    }

    String verses(int startVerse, int endVerse) {
        StringBuilder sb = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            sb.append(verse(i));
            if (i < endVerse) {
                sb.append("\n");
            }
        }
        return sb.toString();
    }

    String sing() {
        return verses(1, days.length);
    }

    private static final String[] days = {
            "first",
            "second",
            "third",