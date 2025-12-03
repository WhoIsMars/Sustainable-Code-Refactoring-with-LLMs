import java.util.List;

class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        String noHyphens = stringToVerify.replace("-", "");
        if (noHyphens.length() != 10 || !noHyphens.matches("\\d{9}[\\dX]")) {
            return false;
        }

        int sum = 0;
        for (int i = 0; i < 10; i++) {
            int value = (i == 9 && noHyphens.charAt(i) == 'X') ? 10 : Character.getNumericValue(noHyphens.charAt(i));
            sum += value * (10 - i);
        }
        return sum % 11 == 0;
    }
}