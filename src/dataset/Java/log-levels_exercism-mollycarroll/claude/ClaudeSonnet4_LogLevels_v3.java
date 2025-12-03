public class LogLevels {
    
    public static String message(String logLine) {
        if (logLine == null || logLine.isEmpty()) {
            return "";
        }
        
        int colonIndex = logLine.indexOf(':');
        if (colonIndex == -1 || colonIndex == logLine.length() - 1) {
            return "";
        }
        
        int start = colonIndex + 1;
        while (start < logLine.length() && logLine.charAt(start) == ' ') {
            start++;
        }
        
        int end = logLine.length() - 1;
        while (end > start && logLine.charAt(end) == ' ') {
            end--;
        }
        
        return start <= end ? logLine.substring(start, end + 1) : "";
    }

    public static String logLevel(String logLine) {
        if (logLine == null || logLine.isEmpty()) {
            return "";
        }
        
        int start = logLine.indexOf('[');
        int end = logLine.indexOf(']');
        
        if (start == -1 || end == -1 || start >= end) {
            return "";
        }
        
        return logLine.substring(start + 1, end).toLowerCase();
    }

    public static String reformat(String logLine) {
        if (logLine == null || logLine.isEmpty()) {
            return "";
        }
        
        String level = logLevel(logLine);
        String msg = message(logLine);
        
        if (level.isEmpty() || msg.isEmpty()) {
            return "";
        }
        
        return msg + " (" + level + ")";
    }
}