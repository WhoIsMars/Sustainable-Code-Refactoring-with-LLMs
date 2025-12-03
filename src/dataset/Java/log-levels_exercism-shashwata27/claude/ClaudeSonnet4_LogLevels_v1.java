import java.util.Locale;

public class LogLevels {
    
    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(':');
        return logLine.substring(colonIndex + 1).strip();
    }

    public static String logLevel(String logLine) {
        int colonIndex = logLine.indexOf(':');
        return logLine.substring(1, colonIndex).toLowerCase(Locale.ROOT);
    }

    public static String reformat(String logLine) {
        int colonIndex = logLine.indexOf(':');
        String message = logLine.substring(colonIndex + 1).strip();
        String level = logLine.substring(1, colonIndex).toLowerCase(Locale.ROOT);
        return message + " (" + level + ")";
    }
}