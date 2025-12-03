import static java.lang.Character.toUpperCase;
import static java.lang.String.format;

public class BeerSong {

    public String sing(final int from, final int count) {
        StringBuilder result = new StringBuilder();
        
        for (int i = from; i >= from - count + 1; i--) {
            if (i == 0) {
                result.append(format(
                        "%s of beer on the wall, %s of beer.\n" +
                                "Go to the store and buy some more, %s of beer on the wall.\n",
                        capitalize(bottles(i)), bottles(i), bottles(99)));
            } else {
                result.append(format(
                        "%s of beer on the wall, %s of beer.\n" +
                                "Take %s down and pass it around, %s of beer on the wall.\n",
                        bottles(i), bottles(i), one(i), bottles(i - 1)));
            }
            
            if (i > from - count + 1) {
                result.append("\n");
            }
        }
        
        return result.append("\n").toString();
    }

    public String singSong() {
        return sing(99, 100);
    }

    private String bottles(int count) {
        switch (count) {
            case 0:
                return "no more bottles";
            case 1:
                return "1 bottle";
            default:
                return count + " bottles";
        }
    }

    private String capitalize(String string) {
        return toUpperCase(string.charAt(0)) + string.substring(1);
    }

    private String one(int count) {
        return count == 1 ? "it" : "one";
    }
}