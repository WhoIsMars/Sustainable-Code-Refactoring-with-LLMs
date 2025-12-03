import java.util.regex.Pattern;

class Bob{
    private static final Pattern SHOUTING_PATTERN = Pattern.compile("([^a-z]*[A-Z][A-Z]+[^a-z]*)");
    private static final Pattern QUESTION_PATTERN = Pattern.compile(".*\\?\\s*$");
    private static final Pattern SILENCE_PATTERN = Pattern.compile("^\\s*$");
    
    public Bob(){
    }
    
    public String hey(String phrase){
        boolean isShouting = SHOUTING_PATTERN.matcher(phrase).matches();
        boolean isQuestion = QUESTION_PATTERN.matcher(phrase).matches();
        boolean isSilence = SILENCE_PATTERN.matcher(phrase).matches();
        
        if (isShouting && isQuestion){
            return "Calm down, I know what I'm doing!";
        } else if (isQuestion){
            return "Sure.";
        } else if (isShouting){
            return "Whoa, chill out!";
        } else if (isSilence){
            return "Fine. Be that way!";
        } else {
            return "Whatever.";
        }
    }
}