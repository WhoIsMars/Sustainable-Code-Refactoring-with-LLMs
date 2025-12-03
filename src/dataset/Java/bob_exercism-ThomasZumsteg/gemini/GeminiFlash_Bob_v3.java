public class Bob {
    public String hey(String greeting) {
        greeting = greeting.trim();
        if (greeting.isEmpty()) {
            return "Fine. Be that way!";
        }

        boolean isQuestion = !greeting.isEmpty() && greeting.charAt(greeting.length() - 1) == '?';

        if (shouting(greeting)) {
            return "Whoa, chill out!";
        } else if (isQuestion) {
            return "Sure.";
        } else {
            return "Whatever.";
        }
    }

    private static boolean shouting(String greeting) {
        boolean hasLetter = false;
        for (int i = 0; i < greeting.length(); i++) {
            char c = greeting.charAt(i);
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