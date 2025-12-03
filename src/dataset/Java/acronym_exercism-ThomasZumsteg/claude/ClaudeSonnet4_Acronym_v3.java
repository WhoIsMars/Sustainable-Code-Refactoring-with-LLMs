public class Acronym {
    public static String generate(String phrase) {
        if (phrase == null || phrase.isEmpty()) {
            return "";
        }
        
        StringBuilder acronym = new StringBuilder();
        boolean nextIsWordStart = true;
        
        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            
            if (Character.isLetter(c)) {
                if (nextIsWordStart) {
                    acronym.append(Character.toUpperCase(c));
                    nextIsWordStart = false;
                } else if (Character.isUpperCase(c)) {
                    acronym.append(c);
                }
            } else {
                nextIsWordStart = true;
            }
        }
        
        return acronym.toString();
    }
}