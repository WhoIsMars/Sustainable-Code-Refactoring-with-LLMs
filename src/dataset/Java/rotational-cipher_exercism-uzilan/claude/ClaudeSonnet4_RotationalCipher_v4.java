import static java.lang.Character.*;

class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey % 26;
    }

    String rotate(String data) {
        if (data.isEmpty()) {
            return data;
        }
        
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

        if (isLowerCase(ch)) {
            return (char) ('a' + (ch - 'a' + shiftKey) % 26);
        } else {
            return (char) ('A' + (ch - 'A' + shiftKey) % 26);
        }
    }
}