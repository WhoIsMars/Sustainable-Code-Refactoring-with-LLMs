class TwelveDays {
    private static final String[] DAYS = {
        "first", "second", "third", "fourth", "fifth", "sixth",
        "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth"
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
        StringBuilder sb = new StringBuilder(200);
        sb.append("On the ").append(DAYS[verseNumber - 1]).append(" day of Christmas my true love gave to me: ");
        
        for (int i = verseNumber - 1; i > 0; i--) {
            sb.append(GIFTS[i]).append(", ");
        }
        
        if (verseNumber > 1) {
            sb.append("and ");
        }
        sb.append(GIFTS[0]).append(".\n");
        
        return sb.toString();
    }

    String verses(int startVerse, int endVerse) {
        StringBuilder sb = new StringBuilder((endVerse - startVerse + 1) * 250);
        
        for (int i = startVerse; i <= endVerse; i++) {
            sb.append(verse(i));
            if (i < endVerse) {
                sb.append("\n");
            }
        }
        
        return sb.toString();
    }

    String sing() {
        return verses(1, 12);
    }
}