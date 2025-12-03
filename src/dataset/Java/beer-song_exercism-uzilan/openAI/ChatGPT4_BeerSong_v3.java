import static java.lang.Character.toUpperCase;
import static java.lang.String.format;

public class BeerSong {

    public String sing(final int from, final int count) {
        StringBuilder song = new StringBuilder();
        for (int i = from; i > from - count; i--) {
            if (i == 0) {
                song.append(format(
                        "%s of beer on the wall, %s of beer.\n" +
                                "Go to the store and buy some more, %s of beer on the wall.\n\n",
                        capitalize(bottles(i)), bottles(i), bottles(99)));
            } else {
                song.append(format(
                        "%s of beer on the wall, %s of beer.\n" +
                                "Take %s down and pass it around, %s of beer on the wall.\n\n",
                        bottles(i), bottles(i), one(i), bottles(i - 1)));
            }
        }
        return song.toString();
    }

    public String singSong() {
        return sing(99, 100);
    }

    private String bottles(int count) {
        return switch (count) {
            case 0 -> "no more bottles";
            case 1 -> "1 bottle";
            default -> count + " bottles";
        };
    }

    private String capitalize(String string) {
        return toUpperCase(string.charAt(0)) + string.substring(1);
    }

    private String one(int count) {
        return count == 1 ? "it" : "one";
    }
}