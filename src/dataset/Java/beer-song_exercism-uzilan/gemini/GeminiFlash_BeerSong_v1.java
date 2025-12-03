public class BeerSong {

    public String sing(final int from, final int count) {
        StringBuilder song = new StringBuilder();
        int to = Math.max(0, from - count + 1);

        for (int i = from; i >= to; i--) {
            song.append(verse(i)).append("\n");
        }

        return song.toString();
    }

    private String verse(int i) {
        if (i == 0) {
            return String.format(
                    "%s of beer on the wall, %s of beer.\n" +
                            "Go to the store and buy some more, %s of beer on the wall.\n",
                    capitalize(bottles(i)), bottles(i), bottles(99));
        } else {
            return String.format(
                    "%s of beer on the wall, %s of beer.\n" +
                            "Take %s down and pass it around, %s of beer on the wall.\n",
                    bottles(i), bottles(i), one(i), bottles(i - 1));
        }
    }


    public String singSong() {
        return sing(99, 100);
    }

    private String bottles(int count) {
        if (count == 0) {
            return "no more bottles";
        } else if (count == 1) {
            return "1 bottle";
        } else {
            return count + " bottles";
        }
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