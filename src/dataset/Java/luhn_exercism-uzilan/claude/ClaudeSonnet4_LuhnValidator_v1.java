import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

class LuhnValidator {

    boolean isValid(String candidate) {
        if (candidate == null || candidate.length() <= 1) {
            return false;
        }

        int length = 0;
        int sum = 0;
        boolean isSecond = false;

        // Process from right to left, skipping spaces
        for (int i = candidate.length() - 1; i >= 0; i--) {
            char c = candidate.charAt(i);
            
            if (c == ' ') {
                continue;
            }
            
            if (c < '0' || c > '9') {
                return false;
            }
            
            length++;
            int digit = c - '0';
            
            if (isSecond) {
                digit *= 2;
                if (digit > 9) {
                    digit -= 9;
                }
            }
            
            sum += digit;
            isSecond = !isSecond;
        }

        return length > 1 && sum % 10 == 0;
    }

    private int doubleOrGet(int index, Integer number) {
        if ((index + 1) % 2 == 0) {
            int doub = number * 2;
            return doub > 9 ? doub - 9 : doub;
        }
        return number;
    }
}