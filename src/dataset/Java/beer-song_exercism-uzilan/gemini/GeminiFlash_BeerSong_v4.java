public class BeerSong {

    public String sing(final int from, final int count) {
        int start = Math.max(0, from - count + 1);
        StringBuilder sb = new StringBuilder();
        for (int i = from; i >= start; i--) {
            if (i == 0) {
                sb.append(capitalize(bottles(i))).append(" of beer on the wall, ").append(bottles(i)).append(".\n");
                sb.append("Go to the store and buy some more, ").append(bottles(99)).append(" of beer on the wall.\n");
            } else {
                sb.append(bottles(i)).append(" of beer on the wall, ").append(bottles(i)).append(" of beer.\n");
                sb.append("Take ").append(one(i)).append(" down and pass it around, ").append(bottles(i - 1)).append(" of beer on the wall.\n");
            }
            if (i > start) {
                sb.append("\n");
            }
        }
        return sb.toString();
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
        if (string == null || string.isEmpty()) {
            return string;
        }
        return Character.toUpperCase(string.charAt(0)) + string.substring(1);
    }

    private String one(int count) {
        return (count == 1) ? "it" : "one";
    }
}