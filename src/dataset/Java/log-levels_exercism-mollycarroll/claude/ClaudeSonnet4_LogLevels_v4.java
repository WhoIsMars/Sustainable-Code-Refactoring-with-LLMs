public class LogLevels {
    
    public static String message(String logLine) {
        int colonIndex = logLine.indexOf(':', 1);
        if (colonIndex == -1) return "";
        
        int start = colonIndex + 1;
        while (start < logLine.length() && logLine.charAt(start) == ' ') {
            start++;
        }
        
        int end = logLine.length();
        while (end > start && logLine.charAt(end - 1) == ' ') {
            end--;
        }
        
        return logLine.substring(start, end);
    }

    public static String logLevel(String logLine) {
        int start = logLine.indexOf('[');
        if (start == -1) return "";
        
        int end = logLine.indexOf(']', start);
        if (end == -1) return "";
        
        return logLine.substring(start + 1, end).toLowerCase();
    }

    public static String reformat(String logLine) {
        int bracketStart = logLine.indexOf('[');
        if (bracketStart == -1) return "";
        
        int bracketEnd = logLine.indexOf(']', bracketStart);
        if (bracketEnd == -1) return "";
        
        int colonIndex = logLine.indexOf(':', bracketEnd);
        if (colonIndex == -1) return "";
        
        int messageStart = colonIndex + 1;
        while (messageStart < logLine.length() && logLine.charAt(messageStart) == ' ') {
            messageStart++;
        }
        
        int messageEnd = logLine.length();
        while (messageEnd > messageStart && logLine.charAt(messageEnd - 1) == ' ') {
            messageEnd--;
        }
        
        return logLine.substring(messageStart, messageEnd) + " (" + 
               logLine.substring(bracketStart + 1, bracketEnd).toLowerCase() + ")";
    }
}