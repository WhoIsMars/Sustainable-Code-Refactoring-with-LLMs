public class LogLevels {
    
    public static String message(String logLine) {
        int start = logLine.indexOf(']');
        return start != -1 ? logLine.substring(start + 1).trim() : "";
    }

    public static String logLevel(String logLine) {
        int start = logLine.indexOf('[');
        int end = logLine.indexOf(']');
        return (start != -1 && end != -1 && end > start) ? 
               logLine.substring(start + 1, end).toLowerCase() : "";
    }

    public static String reformat(String logLine) {
        int start = logLine.indexOf('[');
        int end = logLine.indexOf(']');
        if (start == -1 || end == -1 || end <= start) return "";
        
        String level = logLine.substring(start + 1, end).toLowerCase();
        String message = logLine.substring(end + 1).trim();
        
        return message + " (" + level + ")";
    }
}