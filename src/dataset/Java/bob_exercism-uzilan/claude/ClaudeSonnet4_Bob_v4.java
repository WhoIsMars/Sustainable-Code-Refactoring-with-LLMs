public class Bob {

    String hey(String s) {
        final String trimmed = s.trim();

        if (trimmed.isEmpty()) {
            return "Fine. Be that way!";
        }

        final boolean isQuestion = trimmed.charAt(trimmed.length() - 1) == '?';
        final boolean isUpperCase = isUpperCase(trimmed);

        if (isUpperCase) {
            return isQuestion ? "Calm down, I know what I'm doing!" : "Whoa, chill out!";
        }
        
        return isQuestion ? "Sure." : "Whatever.";
    }

    private boolean isUpperCase(String s) {
        boolean hasLetter = false;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (Character.isLetter(c)) {
                hasLetter = true;
                if (Character.isLowerCase(c)) {
                    return false;
                }
            }
        }
        return hasLetter;
    }
}