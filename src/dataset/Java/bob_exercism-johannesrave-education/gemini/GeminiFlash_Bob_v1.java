class Bob {

    public Bob() {
    }

    public String hey(String phrase) {
        if (phrase == null) {
            return "Whatever.";
        }

        String trimmedPhrase = phrase.trim();

        if (trimmedPhrase.isEmpty()) {
            return "Fine. Be that way!";
        }

        boolean isQuestion = trimmedPhrase.endsWith("?");
        boolean isShouting = false;

        if (!trimmedPhrase.matches(".*[a-z].*")) {
            if (trimmedPhrase.matches(".*[A-Z].*")) {
                isShouting = true;
            }
        }

        if (isShouting && isQuestion) {
            return "Calm down, I know what I'm doing!";
        } else if (isQuestion) {
            return "Sure.";
        } else if (isShouting) {
            return "Whoa, chill out!";
        } else {
            return "Whatever.";
        }
    }
}