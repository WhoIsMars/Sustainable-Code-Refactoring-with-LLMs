class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey;
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder(data.length());
        for (int i = 0; i < data.length(); i++) {
            char c = data.charAt(i);
            c = safelyShiftLetter(c, 'a', 'z');
            c = safelyShiftLetter(c, 'A', 'Z');
            result.append(c);
        }
        return result.toString();
    }

    private char safelyShiftLetter(char letter, char from, char to) {
        if (from <= letter && letter <= to) {
            int base = from;
            int offset = letter - base;
            letter = (char) (base + (offset + shiftKey) % 26);
        }
        return letter;
    }
}