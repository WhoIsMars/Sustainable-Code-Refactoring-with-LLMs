public class LogLevels {

    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(':');
        return (colonIndex == -1) ? "" : logLine.substring(colonIndex + 1).trim();
    }

    public static String logLevel(String logLine) {
        int bracketIndex = logLine.indexOf(']');
        return (bracketIndex <= 1) ? "" : logLine.substring(1, bracketIndex).toLowerCase();
    }

    public static String reformat(String logLine) {
        String message = message(logLine);
        String logLevel = logLevel(logLine);
        return String.format("%s (%s)", message, logLevel);
    }
}