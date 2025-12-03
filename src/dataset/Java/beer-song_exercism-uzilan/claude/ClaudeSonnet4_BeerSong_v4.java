import static java.lang.String.format;

public class BeerSong {

    public String sing(final int from, final int count) {
        StringBuilder result = new StringBuilder((count * 150));
        
        for (int i = from; i >= from - count + 1; i--) {
            if (i == 0) {
                result.append("No more bottles of beer on the wall, no more bottles of beer.\n")
                      .append("Go to the store and buy some more, 99 bottles of beer on the wall.\n");
            } else {
                result.append(bottles(i))
                      .append(" of beer on the wall, ")
                      .append(bottles(i))
                      .append(" of beer.\nTake ")
                      .append(one(i))
                      .append(" down and pass it around, ")
                      .append(bottles(i - 1))
                      .append(" of beer on the wall.\n");
            }
            
            if (i > from - count + 1) {
                result.append('\n');
            }
        }
        
        return result.append('\n').toString();
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