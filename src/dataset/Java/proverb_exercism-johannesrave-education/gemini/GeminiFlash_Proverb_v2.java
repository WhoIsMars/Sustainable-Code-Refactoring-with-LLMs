class Proverb {

    private final String proverb;

    Proverb(String[] words) {
        this.proverb = buildProverb(words);
    }

    private String buildProverb(String[] words) {
        if (words == null || words.length == 0) {
            return "";
        }

        StringBuilder sb = new StringBuilder();
        int len = words.length;

        for (int i = 0; i < len - 1; i++) {
            sb.append("For want of a ").append(words[i]).append(" the ").append(words[i + 1]).append(" was lost.\n");
        }

        sb.append("And all for the want of a ").append(words[0]).append(".");
        return sb.toString();
    }

    String recite() {
        return proverb;
    }
}