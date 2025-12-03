class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey % 26;
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < data.length(); i++) {
            char ch = data.charAt(i);
            result.append(getRotatedLetter(ch));
        }
        return result.toString();
    }

    private char getRotatedLetter(char ch) {
        if (!Character.isLetter(ch)) {
            return ch;
        }

        char base = Character.isLowerCase(ch) ? 'a' : 'A';
        return (char) (base + (ch - base + shiftKey + 26) % 26);
    }
}