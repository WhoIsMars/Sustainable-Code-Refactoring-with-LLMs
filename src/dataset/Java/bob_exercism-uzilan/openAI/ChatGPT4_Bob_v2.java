public class Bob {

    String hey(String s) {
        String trimmed = s.trim();

        if (trimmed.isEmpty()) {
            return "Fine. Be that way!";
        }

        boolean isQuestion = trimmed.charAt(trimmed.length() - 1) == '?';
        boolean isUpperCase = isShouting(trimmed);

        if (isUpperCase) {
            return isQuestion ? "Calm down, I know what I'm doing!" : "Whoa, chill out!";
        }
        return isQuestion ? "Sure." : "Whatever.";
    }

    private boolean isShouting(String s) {
        boolean hasLetters = false;
        for (char c : s.toCharArray()) {
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