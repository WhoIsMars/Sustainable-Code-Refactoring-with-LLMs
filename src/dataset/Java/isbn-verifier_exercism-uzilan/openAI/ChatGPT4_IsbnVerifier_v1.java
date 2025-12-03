import java.util.List;

class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        String noHyphens = stringToVerify.replace("-", "");

        if (noHyphens.length() != 10 || !noHyphens.matches("\\d{9}[\\dX]")) {
            return false;
        }

        int sum = 0;
        for (int i = 0; i < 9; i++) {
            sum += (noHyphens.charAt(i) - '0') * (10 - i);
        }

        char lastChar = noHyphens.charAt(9);
        sum += (lastChar == 'X' ? 10 : lastChar - '0');

        return sum % 11 == 0;
    }
}