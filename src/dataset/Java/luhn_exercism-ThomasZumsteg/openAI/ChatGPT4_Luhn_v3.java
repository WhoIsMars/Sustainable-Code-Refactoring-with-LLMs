import java.util.Arrays;

public class Luhn {
    private final long code;

    public Luhn(Long code) {
        this.code = code;
    }

    public Luhn(Integer code) {
        this.code = code.longValue();
    }

    public int getCheckDigit() {
        return (int) (code % 10);
    }

    public int[] getAddends() {
        String strCode = Long.toString(code);
        int length = strCode.length();
        int[] addends = new int[length];
        boolean doubleDigit = false;

        for (int i = length - 1; i >= 0; i--) {
            int n = strCode.charAt(i) - '0';
            if (doubleDigit) {
                n = n * 2;
                if (n > 9) n -= 9;
            }
            addends[i] = n;
            doubleDigit = !doubleDigit;
        }
        return addends;
    }

    public int getCheckSum() {
        return Arrays.stream(getAddends()).sum();
    }

    public boolean isValid() {
        return getCheckSum() % 10 == 0;
    }

    public static long create(long code) {
        int checkSum = new Luhn(code * 10).getCheckSum() % 10;
        return code * 10 + (checkSum == 0 ? 0 : 10 - checkSum);
    }
}