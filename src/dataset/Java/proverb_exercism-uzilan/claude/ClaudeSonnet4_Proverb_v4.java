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

    private int estimateCapacity() {
        int capacity = 30 + words[0].length();
        for (int i = 0; i < words.length - 1; i++) {
            capacity += 25 + words[i].length() + words[i + 1].length();
        }
        return capacity;
    }
}