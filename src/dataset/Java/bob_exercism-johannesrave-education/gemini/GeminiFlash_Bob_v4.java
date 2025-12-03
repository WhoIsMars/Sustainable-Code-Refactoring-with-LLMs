import java.util.regex.Pattern;

class Bob {
    private static final Pattern SHOUTING = Pattern.compile("([^a-z]*[A-Z][A-Z]+[^a-z]*)");
    private static final Pattern QUESTION = Pattern.compile(".*\\?\\s*$");
    private static final Pattern SILENCE = Pattern.compile("^\\s*$");

    public Bob() {
    }

    public String hey(String phrase) {
        if (phrase == null || phrase.isEmpty()) {
            return "Fine. Be that way!";
        }

        boolean isShouting = SHOUTING.matcher(phrase).matches();
        boolean isQuestion = QUESTION.matcher(phrase).matches();
        boolean isSilence = SILENCE.matcher(phrase).matches();

        if (isShouting && isQuestion) {
            return "Calm down, I know what I'm doing!";
        } else if (isQuestion) {
            return "Sure.";
        } else if (isShouting) {
            return "Whoa, chill out!";
        } else if (isSilence) {
            return "Fine. Be that way!";
        } else {
            return "Whatever.";
        }
    }
}