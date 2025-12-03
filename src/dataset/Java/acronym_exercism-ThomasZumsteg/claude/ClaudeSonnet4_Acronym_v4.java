public class Acronym {
    public static String generate(String phrase) {
        if (phrase == null || phrase.isEmpty()) {
            return "";
        }
        
        StringBuilder acronym = new StringBuilder();
        boolean wordStart = true;
        
        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            
            if (Character.isLetter(c)) {
                if (wordStart) {
                    acronym.append(Character.toUpperCase(c));
                    wordStart = false;
                } else if (Character.isUpperCase(c)) {
                    acronym.append(c);
                }
            } else {
                wordStart = true;
            }
        }
        
        return acronym.toString();
    }
}