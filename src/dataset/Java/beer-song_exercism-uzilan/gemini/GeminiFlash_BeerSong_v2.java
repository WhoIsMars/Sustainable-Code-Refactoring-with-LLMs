public class BeerSong {

    public String sing(final int from, final int count) {
        StringBuilder song = new StringBuilder();
        for (int i = from; i >= from - count + 1; i--) {
            if (i < 0) break;

            String firstLine = bottles(i) + " of beer on the wall, " + bottles(i) + " of beer.\n";
            String secondLine;

            if (i == 0) {
                secondLine = "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
            } else {
                secondLine = "Take " + (i == 1 ? "it" : "one") + " down and pass it around, " + bottles(i - 1) + " of beer on the wall.\n";
            }

            song.append(capitalize(firstLine)).append(secondLine);

            if (i > from - count + 1) {
                song.append("\n");
            }
        }
        return song.toString();
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
        return Character.toUpperCase(string.charAt(0)) + string.substring(1);
    }
}