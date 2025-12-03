class Proverb {

    private static final String LINE = "For want of a %s the %s was lost.\n";
    private static final String ENDING = "And all for the want of a %s.";
    private final String proverb;

    Proverb(String[] words) {
        this.proverb = buildProverb(words);
    }

    private String buildProverb(String[] words) {
        if (words == null || words.length == 0) {
            return "";
        }

        StringBuilder proverbBuilder = new StringBuilder();
        int length = words.length;

        for (int i = 0; i < length - 1; i++) {
            proverbBuilder.append(String.format(LINE, words[i], words[i + 1]));
        }

        proverbBuilder.append(String.format(ENDING, words[0]));
        return proverbBuilder.toString();
    }

    String recite() {
        return proverb;
    }
}