class Proverb {

    static private final String line = "For want of a %s the %s was lost.\n";
    static private final String ending = "And all for the want of a %s.";
    private String proverb;
    
    Proverb(String[] words) {
        if (words.length == 0) {
            this.proverb = "";
            return;
        }
        
        StringBuilder sb = new StringBuilder(words.length * 50);
        for (int i = 0; i < words.length - 1; i++) {
            sb.append("For want of a ").append(words[i])
              .append(" the ").append(words[i+1])
              .append(" was lost.\n");
        }
        sb.append("And all for the want of a ").append(words[0]).append(".");
        this.proverb = sb.toString();
    }

    String recite() {
        return proverb;
    }
}