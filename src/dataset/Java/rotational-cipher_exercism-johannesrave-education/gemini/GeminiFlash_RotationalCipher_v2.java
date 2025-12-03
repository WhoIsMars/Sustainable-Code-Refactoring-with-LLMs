class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey % 26;
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < data.length(); i++) {
            char c = data.charAt(i);
            if (Character.isLetter(c)) {
                char base = Character.isLowerCase(c) ? 'a' : 'A';
                c = (char) (base + (c - base + shiftKey) % 26);
            }
            result.append(c);
        }
        return result.toString();
    }
}