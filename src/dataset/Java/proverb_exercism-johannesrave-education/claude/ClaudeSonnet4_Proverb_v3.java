class Proverb {

    private static final String LINE_FORMAT = "For want of a %s the %s was lost.\n";
    private static final String ENDING_FORMAT = "And all for the want of a %s.";
    private final String proverb;
    
    Proverb(String[] words) {
        if (words.length == 0) {
            this.proverb = "";
            return;
        }
        
        int capacity = estimateCapacity(words);
        StringBuilder builder = new StringBuilder(capacity);
        
        for (int i = 0; i < words.length - 1; i++) {
            builder.append("For want of a ").append(words[i])
                   .append(" the ").append(words[i + 1])
                   .append(" was lost.\n");
        }
        builder.append("And all for the want of a ").append(words[0]).append('.');
        
        this.proverb = builder.toString();
    }
    
    private static int estimateCapacity(String[] words) {
        int totalWordLength = 0;
        for (String word : words) {
            totalWordLength += word.length();
        }
        return totalWordLength * 2 + words.length * 35;
    }

    String recite() {
        return proverb;
    }
}