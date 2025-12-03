public class Bob {

    String hey(String s) {
        String trimmed = s.trim();

        if (trimmed.isEmpty()) {
            return "Fine. Be that way!";
        }

        boolean isQuestion = trimmed.charAt(trimmed.length() - 1) == '?';
        boolean hasLetters = false;
        boolean isUpperCase = true;

        for (char c : trimmed.toCharArray()) {
            if (Character.isLetter(c)) {
                hasLetters = true;
                if (!Character.isUpperCase(c)) {
                    isUpperCase = false;
                    break;
                }
            }
        }

        if (hasLetters && isUpperCase) {
            return isQuestion ? "Calm down, I know what I'm doing!" : "Whoa, chill out!";
        }

        if (isQuestion) {
            return "Sure.";
        }

        return "Whatever.";
    }
}