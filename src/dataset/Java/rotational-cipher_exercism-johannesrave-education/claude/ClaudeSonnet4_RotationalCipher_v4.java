import java.util.stream.Collectors;

class RotationalCipher {

    private final int shiftKey;
    private final int normalizedShift;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey;
        this.normalizedShift = ((shiftKey % 26) + 26) % 26;
    }

    String rotate(String data) {
        if (data.isEmpty()) {
            return data;
        }
        
        StringBuilder result = new StringBuilder(data.length());
        for (int i = 0; i < data.length(); i++) {
            char c = data.charAt(i);
            result.append(shiftChar(c));
        }
        return result.toString();
    }

    private char shiftChar(char c) {
        if (c >= 'a' && c <= 'z') {
            return (char) ('a' + (c - 'a' + normalizedShift) % 26);
        } else if (c >= 'A' && c <= 'Z') {
            return (char) ('A' + (c - 'A' + normalizedShift) % 26);
        }
        return c;
    }
}