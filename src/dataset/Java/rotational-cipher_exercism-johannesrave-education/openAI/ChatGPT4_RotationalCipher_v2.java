class RotationalCipher {

    private final int shiftKey;

    RotationalCipher(int shiftKey) {
        this.shiftKey = shiftKey % 26; // Optimize shiftKey to avoid unnecessary cycles
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder(data.length()); // Use StringBuilder for efficiency
        for (char letter : data.toCharArray()) {
            result.append(shiftLetter(letter));
        }
        return result.toString();
    }

    private char shiftLetter(char letter) {
        if (letter >= 'a' && letter <= 'z') {
            return (char) ('a' + (letter - 'a' + shiftKey) % 26);
        } else if (letter >= 'A' && letter <= 'Z') {
            return (char) ('A' + (letter - 'A' + shiftKey) % 26);
        }
        return letter; // Non-alphabetic characters remain unchanged
    }
}