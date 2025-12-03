class Proverb {

    private static final String LINE = "For want of a %s the %s was lost.\n";
    private static final String ENDING = "And all for the want of a %s.";
    private final String proverb;

    Proverb(String[] words) {
        if (words == null || words.length == 0) {
            this.proverb = "";
        } else {
            StringBuilder proverbBuilder = new StringBuilder();
            for (int i = 0, len = words.length - 1; i < len; i++) {
                proverbBuilder.append(String.format(LINE, words[i], words[i + 1]));
            }
            proverbBuilder.append(String.format(ENDING, words[0]));
            this.proverb = proverbBuilder.toString();
        }
    }

    String recite() {
        return proverb;
    }
}