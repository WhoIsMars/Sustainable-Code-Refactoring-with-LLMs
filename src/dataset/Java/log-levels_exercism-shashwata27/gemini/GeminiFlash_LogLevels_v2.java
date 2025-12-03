import java.util.Locale;

public class LogLevels {

    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(":");
        return logLine.substring(colonIndex + 1).strip();
    }

    public static String logLevel(String logLine) {
        int colonIndex = logLine.indexOf(":");
        return logLine.substring(1, colonIndex - 1).toLowerCase(Locale.ROOT);
    }

    public static String reformat(String logLine) {
        return message(logLine) + " (" + logLevel(logLine) + ")";
    }
}