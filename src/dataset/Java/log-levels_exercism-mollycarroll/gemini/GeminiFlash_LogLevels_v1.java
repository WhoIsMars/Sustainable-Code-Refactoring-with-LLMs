public class LogLevels {

    public static String message(String logLine) {
        int start = logLine.indexOf(":");
        if (start == -1) {
            return logLine.trim(); // Or handle the error as appropriate
        }
        return logLine.substring(start + 1).trim();
    }

    public static String logLevel(String logLine) {
        int start = logLine.indexOf("[");
        int end = logLine.indexOf("]");
        if (start == -1 || end == -1 || end <= start) {
            return ""; // Or handle the error as appropriate
        }
        return logLine.substring(start + 1, end).trim().toLowerCase();
    }

    public static String reformat(String logLine) {
        return message(logLine) + " (" + logLevel(logLine) + ")";
    }
}