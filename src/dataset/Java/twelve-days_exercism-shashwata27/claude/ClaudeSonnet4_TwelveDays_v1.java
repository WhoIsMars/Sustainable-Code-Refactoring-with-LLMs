import java.util.List;
import java.util.Map;

class TwelveDays {
    private static final String[][] DAYS_DATA = {
            {"first", "a Partridge in a Pear Tree."},
            {"second", "two Turtle Doves"},
            {"third", "three French Hens"},
            {"fourth", "four Calling Birds"},
            {"fifth", "five Gold Rings"},
            {"sixth", "six Geese-a-Laying"},
            {"seventh", "seven Swans-a-Swimming"},
            {"eighth", "eight Maids-a-Milking"},
            {"ninth", "nine Ladies Dancing"},
            {"tenth", "ten Lords-a-Leaping"},
            {"eleventh", "eleven Pipers Piping"},
            {"twelfth", "twelve Drummers Drumming"}
    };

    String verse(int verseNumber) {
        if (verseNumber == 1) {
            return "On the first day of Christmas my true love gave to me: a Partridge in a Pear Tree.\n";
        }
        
        StringBuilder sb = new StringBuilder();
        sb.append("On the ").append(DAYS_DATA[verseNumber - 1][0])
          .append(" day of Christmas my true love gave to me: ");
        
        for (int i = verseNumber - 1; i >= 0; i--) {
            sb.append(DAYS_DATA[i][1]);
            if (i > 0) {
                sb.append(", ");
            }
        }
        
        return sb.append("\n").toString();
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