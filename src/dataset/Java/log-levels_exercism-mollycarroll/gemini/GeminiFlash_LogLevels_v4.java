public class LogLevels {

    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(":");
        if (colonIndex == -1 || colonIndex == logLine.length() - 1) {
            return ""; // Or handle the error as appropriate
        }
        return logLine.substring(colonIndex + 1).trim();
    }

    public static String logLevel(String logLine) {
        int openBracketIndex = logLine.indexOf("[");
        int closeBracketIndex = logLine.indexOf("]");

        if (openBracketIndex == -1 || closeBracketIndex == -1 || openBracketIndex >= closeBracketIndex) {
            return ""; // Or handle the error as appropriate
        }

        return logLine.substring(openBracketIndex + 1, closeBracketIndex).trim().toLowerCase();
    }

    public static String reformat(String logLine) {
        String level = logLevel(logLine);
        String message = message(logLine);

        return message + " (" + level + ")";
    }
}