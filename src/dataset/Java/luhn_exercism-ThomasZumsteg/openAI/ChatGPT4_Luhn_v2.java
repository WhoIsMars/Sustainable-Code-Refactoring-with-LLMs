import java.util.stream.IntStream;

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
        int[] intCode = new int[length];
        for (int i = length - 1; i >= 0; i--) {
            int n = strCode.charAt(i) - '0';
            if ((length - i) % 2 == 0) {
                int doubled = n * 2;
                intCode[i] = doubled > 9 ? doubled - 9 : doubled;
            } else {
                intCode[i] = n;
            }
        }
        return intCode;
    }

    public int getCheckSum() {
        return IntStream.of(getAddends()).sum();
    }

    public boolean isValid() {
        return getCheckSum() % 10 == 0;
    }

    public static long create(long code) {
        int checkSum = new Luhn(code * 10).getCheckSum() % 10;
        return code * 10 + (checkSum == 0 ? 0 : 10 - checkSum);
    }
}