public class Trinary {
    public static int toDecimal(String trinary) {
        if (trinary == null || trinary.isEmpty()) {
            return 0;
        }

        int decimal = 0;
        int length = trinary.length();

        for (int i = 0; i < length; i++) {
            char c = trinary.charAt(i);
            int digit = c - '0';

            if (digit >= 0 && digit <= 2) {
                decimal = decimal * 3 + digit;
            } else {
                return 0;
            }
        }

        return decimal;
    }
}