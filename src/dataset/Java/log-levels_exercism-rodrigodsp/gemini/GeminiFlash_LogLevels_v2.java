public class LogLevels {

    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(':');
        return logLine.substring(colonIndex + 1).trim();
    }

    public static String logLevel(String logLine) {
        return logLine.substring(1, logLine.indexOf(']')).toLowerCase();
    }

    public static String reformat(String logLine) {
        int colonIndex = logLine.indexOf(':');
        int bracketIndex = logLine.indexOf(']');

        String message = logLine.substring(colonIndex + 1).trim();
        String logLevel = logLine.substring(1, bracketIndex).toLowerCase();

        return message + " (" + logLevel + ")";
    }
}