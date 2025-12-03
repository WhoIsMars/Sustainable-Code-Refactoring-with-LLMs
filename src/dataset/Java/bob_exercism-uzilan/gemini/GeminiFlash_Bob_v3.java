public class Bob {

    String hey(String s) {
        final String trimmed = s.trim();

        if (trimmed.isEmpty()) {
            return "Fine. Be that way!";
        }

        final boolean isQuestion = trimmed.endsWith("?");
        final boolean isUpperCase = isUpperCase(trimmed);

        if (isUpperCase) {
            if (isQuestion) {
                return "Calm down, I know what I'm doing!";
            } else {
                return "Whoa, chill out!";
            }
        }
        if (isQuestion) {
            return "Sure.";
        }
        return "Whatever.";
    }


    private boolean isUpperCase(String s) {
        boolean hasLetters = false;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (Character.isLetter(c)) {
                hasLetters = true;
                if (Character.isLowerCase(c)) {
                    return false;
                }
            }
        }
        return hasLetters;
    }
}