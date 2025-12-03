class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey % 26; 
    }

    String rotate(String data) { 
        char[] chars = data.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            chars[i] = shiftChar(chars[i]);
        }
        return new String(chars);
    }

    private char shiftChar(char c) {
        if (c >= 'a' && c <= 'z') {
            return (char) ((c - 'a' + shiftKey) % 26 + 'a');
        } else if (c >= 'A' && c <= 'Z') {
            return (char) ((c - 'A' + shiftKey) % 26 + 'A');
        }
        return c;
    }
}