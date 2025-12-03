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
        StringBuilder verse = new StringBuilder("On the ").append(DAYS[verseNumber - 1]).append(" day of Christmas my true love gave to me: ");
        for (int i = verseNumber; i > 1; i--) {
            verse.append(GIFTS[i - 1]).append(", ");
        }
        verse.append(verseNumber != 1 ? "and " : "").append(GIFTS[0]).append(".\n");
        return verse.toString();
    }

    String verses(int startVerse, int endVerse) {
        StringBuilder verses = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            verses.append(this.verse(i));
            if (i < endVerse) {
                verses.append("\n");
            }
        }
        return verses.toString();
    }

    String sing() {
        return this.verses(1, 12);
    }
}