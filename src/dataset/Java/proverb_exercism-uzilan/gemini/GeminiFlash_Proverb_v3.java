class Proverb {

    private final String[] words;

    Proverb(final String[] words) {
        this.words = words;
    }

    String recite() {
        if (words.length == 0) {
            return "";
        }

        final StringBuilder sb = new StringBuilder();
        int n = words.length;
        for (int i = 0; i < n - 1; i++) {
            sb.append(String.format("For want of a %s the %s was lost.\n", words[i], words[i + 1]));
        }
        sb.append(String.format("And all for the want of a %s.", words[0]));
        return sb.toString();
    }
}