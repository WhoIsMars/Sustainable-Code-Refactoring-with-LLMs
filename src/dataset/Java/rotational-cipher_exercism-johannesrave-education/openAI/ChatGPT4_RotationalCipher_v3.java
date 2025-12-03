class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey % 26;
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder(data.length());
        for (char c : data.toCharArray()) {
            result.append(shiftCharacter(c));
        }
        return result.toString();
    }

    private char shiftCharacter(char c) {
        if (c >= 'a' && c <= 'z') {
            return (char) ('a' + (c - 'a' + shiftKey) % 26);
        } else if (c >= 'A' && c <= 'Z') {
            return (char) ('A' + (c - 'A' + shiftKey) % 26);
        }
        return c;
    }
}