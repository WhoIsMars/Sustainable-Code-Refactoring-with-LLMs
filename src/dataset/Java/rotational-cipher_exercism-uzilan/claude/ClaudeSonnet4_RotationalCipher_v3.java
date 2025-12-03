import static java.lang.Character.*;

class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = ((shiftKey % 26) + 26) % 26;
    }

    String rotate(String data) {
        if (data.isEmpty()) {
            return data;
        }
        
        StringBuilder result = new StringBuilder(data.length());
        for (int i = 0; i < data.length(); i++) {
            result.append(getRotatedLetter(data.codePointAt(i)));
        }
        return result.toString();
    }

    private char getRotatedLetter(int codePoint) {
        final char ch = (char) codePoint;
        if (!isLetter(ch)) {
            return ch;
        }

        final boolean isLower = isLowerCase(ch);
        final char base = isLower ? 'a' : 'A';
        final int shifted = (ch - base + shiftKey) % 26;
        
        return (char) (base + shifted);
    }
}