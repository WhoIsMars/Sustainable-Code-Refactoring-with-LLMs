import java.util.regex.Pattern;

class Bob {
    private static final Pattern SHOUTING = Pattern.compile("^[^a-z]*[A-Z][^a-z]*$");
    private static final Pattern QUESTION = Pattern.compile(".*\\?\\s*$");
    private static final Pattern SILENCE = Pattern.compile("^\\s*$");

    public Bob() {
    }

    public String hey(String phrase) {
        if (phrase == null || SILENCE.matcher(phrase).matches()) {
            return "Fine. Be that way!";
        }
        boolean isShouting = SHOUTING.matcher(phrase).matches();
        boolean isQuestion = QUESTION.matcher(phrase).matches();

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