public class LogLevels {

    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(":");
        if (colonIndex == -1) {
            return logLine.trim();
        }
        return logLine.substring(colonIndex + 1).trim();
    }

    public static String logLevel(String logLine) {
        int startIndex = logLine.indexOf("[");
        int endIndex = logLine.indexOf("]");
        if (startIndex == -1 || endIndex == -1) {
            return "";
        }
        return logLine.substring(startIndex + 1, endIndex).trim().toLowerCase();
    }

    public static String reformat(String logLine) {
        String message = message(logLine);
        String logLevel = logLevel(logLine);
        return message + " (" + logLevel + ")";
    }
}