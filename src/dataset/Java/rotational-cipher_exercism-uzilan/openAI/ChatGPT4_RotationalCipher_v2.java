class RotationalCipher {

    private final char[] lowerCaseMap = new char[26];
    private final char[] upperCaseMap = new char[26];

    RotationalCipher(int shiftKey) {
        for (int i = 0; i < 26; i++) {
            lowerCaseMap[i] = (char) ('a' + (i + shiftKey) % 26);
            upperCaseMap[i] = (char) ('A' + (i + shiftKey) % 26);
        }
    }

    String rotate(String data) {
        StringBuilder result = new StringBuilder(data.length());
        for (char ch : data.toCharArray()) {
            result.append(getRotatedLetter(ch));
        }
        return result.toString();
    }

    private char getRotatedLetter(char ch) {
        if (ch >= 'a' && ch <= 'z') {
            return lowerCaseMap[ch - 'a'];
        } else if (ch >= 'A' && ch <= 'Z') {
            return upperCaseMap[ch - 'A'];
        }
        return ch;
    }
}