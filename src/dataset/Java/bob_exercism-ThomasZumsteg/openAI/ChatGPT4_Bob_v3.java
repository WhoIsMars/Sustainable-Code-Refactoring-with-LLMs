public class Bob {
    public String hey(String greeting) {
        if (greeting == null || (greeting = greeting.trim()).isEmpty()) {
            return "Fine. Be that way!";
        }
        if (shouting(greeting)) {
            return "Whoa, chill out!";
        }
        if (greeting.endsWith("?")) {
            return "Sure.";
        }
        return "Whatever.";
    }

    private static boolean shouting(String greeting) {
        boolean hasUppercase = false;
        for (int i = 0, len = greeting.length(); i < len; i++) {
            char c = greeting.charAt(i);
            if (Character.isLowerCase(c)) {
                return false;
            }
            if (Character.isUpperCase(c)) {
                hasUppercase = true;
            }
        }
        return hasUppercase;
    }
}