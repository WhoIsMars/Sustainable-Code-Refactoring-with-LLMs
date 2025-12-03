import static java.lang.Character.toUpperCase;

public class BeerSong {

    public String sing(final int from, final int count) {
        StringBuilder song = new StringBuilder();
        int start = Math.max(0, from - count + 1);

        for (int i = from; i >= start; i--) {
            if (i == 0) {
                song.append(capitalize(bottles(i))).append(" of beer on the wall, ").append(bottles(i)).append(" of beer.\n");
                song.append("Go to the store and buy some more, ").append(bottles(99)).append(" of beer on the wall.\n");
            } else {
                song.append(bottles(i)).append(" of beer on the wall, ").append(bottles(i)).append(" of beer.\n");
                song.append("Take ").append(one(i)).append(" down and pass it around, ").append(bottles(i - 1)).append(" of beer on the wall.\n");
            }
            if (i > start) {
                song.append("\n");
            }
        }
        return song.toString();
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
        if (string == null || string.isEmpty()) {
            return string;
        }
        return toUpperCase(string.charAt(0)) + string.substring(1);
    }

    private String one(int count) {
        return (count == 1) ? "it" : "one";
    }
}