class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = ((shiftKey % 26) + 26) % 26;
    }

    String rotate(String data) {
        if (data.isEmpty()) {
            return data;
        }
        
        char[] chars = data.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            chars[i] = shiftChar(chars[i]);
        }
        return new String(chars);
    }

    private char shiftChar(char c) {
        if (c >= 'a' && c <= 'z') {
            return (char) ('a' + (c - 'a' + shiftKey) % 26);
        } else if (c >= 'A' && c <= 'Z') {
            return (char) ('A' + (c - 'A' + shiftKey) % 26);
        }
        return c;
    }

    private int safelyShiftLetter(int letter, char from, char to) {
        if (from <= letter && letter <= to) {
            letter += (letter + shiftKey > to) ? shiftKey-26 : shiftKey; 
        }
        return letter;
    }
}