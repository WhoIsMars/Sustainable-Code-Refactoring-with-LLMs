public class LogLevels {
    
    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(':');
        if (colonIndex == -1) return logLine;
        
        int start = colonIndex + 1;
        int end = logLine.length();
        
        // Skip leading whitespace
        while (start < end && logLine.charAt(start) == ' ') {
            start++;
        }
        
        // Skip trailing whitespace
        while (end > start && logLine.charAt(end - 1) == ' ') {
            end--;
        }
        
        return logLine.substring(start, end);
    }

    public static String logLevel(String logLine) {
        int start = logLine.indexOf('[');
        int end = logLine.indexOf(']');
        
        if (start == -1 || end == -1 || start >= end) {
            return "";
        }
        
        return logLine.substring(start + 1, end).toLowerCase();
    }

    public static String reformat(String logLine) {
        int bracketStart = logLine.indexOf('[');
        int bracketEnd = logLine.indexOf(']');
        int colonIndex = logLine.indexOf(':');
        
        if (bracketStart == -1 || bracketEnd == -1 || colonIndex == -1) {
            return logLine;
        }
        
        // Extract log level
        String level = logLine.substring(bracketStart + 1, bracketEnd).toLowerCase();
        
        // Extract message
        int messageStart = colonIndex + 1;
        int messageEnd = logLine.length();
        
        // Skip leading whitespace
        while (messageStart < messageEnd && logLine.charAt(messageStart) == ' ') {
            messageStart++;
        }
        
        // Skip trailing whitespace
        while (messageEnd > messageStart && logLine.charAt(messageEnd - 1) == ' ') {
            messageEnd--;
        }
        
        String message = logLine.substring(messageStart, messageEnd);
        
        return message + " (" + level + ")";
    }
}