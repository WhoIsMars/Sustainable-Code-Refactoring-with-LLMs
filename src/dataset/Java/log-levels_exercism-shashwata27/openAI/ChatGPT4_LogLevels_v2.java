public class LogLevels {

    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(':');
        return logLine.substring(colonIndex + 1).strip();
    }

    public static String logLevel(String logLine) {
        int start = logLine.indexOf('[') + 1;
        int end = logLine.indexOf(']');
        return logLine.substring(start, end).toLowerCase();
    }

    public static String reformat(String logLine) {
        int colonIndex = logLine.indexOf(':');
        int start = logLine.indexOf('[') + 1;
        int end = logLine.indexOf(']');
        String message = logLine.substring(colonIndex + 1).strip();
        String level = logLine.substring(start, end).toLowerCase();
        return message + " (" + level + ")";
    }
}