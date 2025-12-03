class TwelveDays {
    private static final String[] DAYS = {
            "first", "second", "third", "fourth",
            "fifth", "sixth", "seventh", "eighth",
            "ninth", "tenth", "eleventh", "twelfth"
    };
    private static final String[] GIFTS = {
            "a Partridge in a Pear Tree",
            "two Turtle Doves",
            "three French Hens",
            "four Calling Birds",
            "five Gold Rings",
            "six Geese-a-Laying",
            "seven Swans-a-Swimming",
            "eight Maids-a-Milking",
            "nine Ladies Dancing",
            "ten Lords-a-Leaping",
            "eleven Pipers Piping",
            "twelve Drummers Drumming"
    };

    String verse(int verseNumber) {
        StringBuilder verseBuilder = new StringBuilder("On the ").append(DAYS[verseNumber - 1])
                .append(" day of Christmas my true love gave to me: ");

        for (int i = verseNumber; i > 1; i--) {
            verseBuilder.append(GIFTS[i - 1]).append(", ");
        }

        verseBuilder.append(verseNumber != 1 ? "and " : "").append(GIFTS[0]).append(".\n");

        return verseBuilder.toString();
    }

    String verses(int startVerse, int endVerse) {
        StringBuilder versesBuilder = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            versesBuilder.append(this.verse(i));
            if (i < endVerse) {
                versesBuilder.append("\n");
            }
        }
        return versesBuilder.toString();
    }

    String sing() {
        return this.verses(1, 12);
    }
}