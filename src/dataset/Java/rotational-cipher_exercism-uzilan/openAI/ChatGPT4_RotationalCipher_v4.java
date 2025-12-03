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
        for (int i = 0; i < data.length(); i++) {
            char ch = data.charAt(i);
            if (Character.isLowerCase(ch)) {
                result.append(lowerCaseMap[ch - 'a']);
            } else if (Character.isUpperCase(ch)) {
                result.append(upperCaseMap[ch - 'A']);
            } else {
                result.append(ch);
            }
        }
        return result.toString();
    }
}