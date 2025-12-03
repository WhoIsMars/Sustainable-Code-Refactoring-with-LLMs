public class Bob {
    public String hey(String greeting) {
        if (greeting == null || greeting.isBlank()) {
            return "Fine. Be that way!";
        }
        greeting = greeting.trim();
        if (isShouting(greeting)) {
            return "Whoa, chill out!";
        }
        if (greeting.endsWith("?")) {
            return "Sure.";
        }
        return "Whatever.";
    }

    private static boolean isShouting(String greeting) {
        boolean hasUppercase = false;
        for (int i = 0; i < greeting.length(); i++) {
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