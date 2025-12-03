class Proverb {

    private final String proverb;

    Proverb(String[] words) {
        this.proverb = buildProverb(words);
    }

    private String buildProverb(String[] words) {
        if (words == null || words.length == 0) {
            return "";
        }

        StringBuilder proverbBuilder = new StringBuilder();
        for (int i = 0; i < words.length - 1; i++) {
            proverbBuilder.append("For want of a ").append(words[i]).append(" the ").append(words[i + 1]).append(" was lost.\n");
        }
        proverbBuilder.append("And all for the want of a ").append(words[0]).append(".");

        return proverbBuilder.toString();
    }

    String recite() {
        return proverb;
    }
}