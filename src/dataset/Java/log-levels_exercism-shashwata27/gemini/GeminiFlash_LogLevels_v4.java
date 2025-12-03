import java.util.Locale;

public class LogLevels {

    public static String message(String logLine) {
        int index = logLine.indexOf(':');
        return logLine.substring(index + 1).strip();
    }

    public static String logLevel(String logLine) {
        int startIndex = logLine.indexOf('[') + 1;
        int endIndex = logLine.indexOf(']');
        return logLine.substring(startIndex, endIndex).toLowerCase(Locale.ROOT);
    }

    public static String reformat(String logLine) {
        return message(logLine) + " (" + logLevel(logLine) + ")";
    }
}