import static java.lang.Character.*;

class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey % 26;
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder(data.length());
        for (int i = 0; i < data.length(); i++) {
            result.append(getRotatedLetter(data.charAt(i)));
        }
        return result.toString();
    }

    private char getRotatedLetter(char ch) {
        if (!isLetter(ch)) {
            return ch;
        }

        char base = isLowerCase(ch) ? 'a' : 'A';
        int offset = ch - base;
        int rotatedOffset = (offset + shiftKey) % 26;
        return (char) (base + rotatedOffset);
    }
}