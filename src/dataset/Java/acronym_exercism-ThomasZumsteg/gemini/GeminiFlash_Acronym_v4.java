public class Acronym {
    public static String generate(String phrase) {
        String[] words = phrase.split("\\W+");
        StringBuilder acronym = new StringBuilder();
        for (String word : words) {
            if (word.isEmpty()) continue;
            acronym.append(Character.toUpperCase(word.charAt(0)));
            if (word.length() > 1) {
                for (int i = 1; i < word.length(); i++) {
                    char c = word.charAt(i);
                    if (Character.isUpperCase(c)) {
                        acronym.append(c);
                    }
                }
            }
        }
        return acronym.toString();
    }
}