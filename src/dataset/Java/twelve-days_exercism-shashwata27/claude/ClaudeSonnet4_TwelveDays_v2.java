import java.util.List;

class TwelveDays {
    private static final String[] ORDINALS = {
        "", "first", "second", "third", "fourth", "fifth", "sixth",
        "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth"
    };
    
    private static final String[] GIFTS = {
        "", "a Partridge in a Pear Tree.", "two Turtle Doves",
        "three French Hens", "four Calling Birds", "five Gold Rings",
        "six Geese-a-Laying", "seven Swans-a-Swimming", "eight Maids-a-Milking",
        "nine Ladies Dancing", "ten Lords-a-Leaping", "eleven Pipers Piping",
        "twelve Drummers Drumming"
    };

    String verse(int verseNumber) {
        StringBuilder sb = new StringBuilder();
        sb.append("On the ").append(ORDINALS[verseNumber])
          .append(" day of Christmas my true love gave to me: ");
        
        if (verseNumber == 1) {
            sb.append("a Partridge in a Pear Tree.\n");
        } else {
            for (int i = verseNumber; i > 1; i--) {
                sb.append(GIFTS[i]).append(", ");
            }
            sb.append("and ").append(GIFTS[1]).append("\n");
        }
        
        return sb.toString();
    }

    String verses(int startVerse, int endVerse) {
        StringBuilder sb = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            sb.append(verse(i));
            if (i != endVerse) {
                sb.append("\n");
            }
        }
        return sb.toString();
    }
    
    String sing() {
        return verses(1, 12);
    }
}