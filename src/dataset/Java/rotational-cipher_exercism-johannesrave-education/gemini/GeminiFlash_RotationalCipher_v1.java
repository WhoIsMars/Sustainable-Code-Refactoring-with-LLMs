class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey;
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < data.length(); i++) {
            char c = data.charAt(i);
            result.append(shiftChar(c));
        }
        return result.toString();
    }

    private char shiftChar(char c) {
        if (c >= 'a' && c <= 'z') {
            return (char) ('a' + (c - 'a' + shiftKey) % 26);
        } else if (c >= 'A' && c <= 'Z') {
            return (char) ('A' + (c - 'A' + shiftKey) % 26);
        } else {
            return c;
        }
    }
}