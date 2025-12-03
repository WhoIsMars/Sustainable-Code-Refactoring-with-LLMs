import java.util.List;

class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        String cleaned = stringToVerify.replace("-", "");
        if (cleaned.length() != 10 || !cleaned.matches("\\d{9}[\\dX]")) {
            return false;
        }

        int sum = 0;
        for (int i = 0; i < 10; i++) {
            int value = (cleaned.charAt(i) == 'X') ? 10 : (cleaned.charAt(i) - '0');
            sum += value * (10 - i);
        }

        return sum % 11 == 0;
    }
}