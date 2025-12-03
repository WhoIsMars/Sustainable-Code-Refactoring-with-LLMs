public class Bob {
    public String hey(String greeting) {
        greeting = greeting.trim();
        if (greeting.isEmpty()) {
            return "Fine. Be that way!";
        }

        boolean isShouting = false;
        boolean isQuestion = false;

        int length = greeting.length();
        if (length > 0 && greeting.charAt(length - 1) == '?') {
            isQuestion = true;
        }

        boolean hasLetters = false;
        for (int i = 0; i < length; i++) {
            char c = greeting.charAt(i);
            if (Character.isLetter(c)) {
                hasLetters = true;
                if (Character.isLowerCase(c)) {
                    isShouting = false;
                    break;
                } else {
                    isShouting = true;
                }
            }
        }

        if (hasLetters && isShouting) {
            return "Whoa, chill out!";
        } else if (isQuestion) {
            return "Sure.";
        } else {
            return "Whatever.";
        }
    }
}