import java.util.Arrays;

class Proverb {

    private final String[] words;

    Proverb(final String[] words) {
        this.words = Arrays.copyOf(words, words.length);
    }

    String recite() {
        if (words.length == 0) {
            return "";
        }

        final StringBuilder sb = new StringBuilder(estimateCapacity());
        
        for (int i = 0; i < words.length - 1; i++) {
            sb.append("For want of a ").append(words[i])
              .append(" the ").append(words[i + 1])
              .append(" was lost.\n");
        }
        
        sb.append("And all for the want of a ").append(words[0]).append(".");
        return sb.toString();
    }

    private void helper(final StringBuilder sb, final String[] words) {
        if (words.length < 2) {
            return;
        }
        sb.append(String.format("For want of a %s the %s was lost.\n", words[0], words[1]));
        helper(sb, Arrays.copyOfRange(words, 1, words.length));
    }

    private int estimateCapacity() {
        if (words.length == 0) return 0;
        
        int totalWordLength = 0;
        for (String word : words) {
            totalWordLength += word.length();
        }
        
        return (words.length - 1) * 30 + totalWordLength * 2 + 30;
    }
}