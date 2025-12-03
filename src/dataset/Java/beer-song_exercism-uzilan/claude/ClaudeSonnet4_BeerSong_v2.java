import static java.lang.String.format;

public class BeerSong {

    public String sing(final int from, final int count) {
        StringBuilder result = new StringBuilder();
        
        for (int i = from; i >= from - count + 1; i--) {
            if (i == 0) {
                result.append(format(
                        "No more bottles of beer on the wall, no more bottles of beer.\n" +
                        "Go to the store and buy some more, 99 bottles of beer on the wall.\n"));
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
        
        result.append("\n");
        return result.toString();
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

    private String one(int count) {
        return count == 1 ? "it" : "one";
    }
}