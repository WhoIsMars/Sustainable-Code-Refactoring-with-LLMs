import java.util.Arrays;

public class Luhn {
    private long code;

    public Luhn(Long code) {
        this.code = code;
    }

    public Luhn(Integer code){
        this.code = code.longValue();
    }

    public int getCheckDigit() {
        return (int)(code % 10L);
    }

    public int[] getAddends() {
        // Calculate length without string conversion
        long temp = code;
        int length = (temp == 0) ? 1 : 0;
        while (temp > 0) {
            length++;
            temp /= 10;
        }
        
        int[] intCode = new int[length];
        temp = code;
        
        // Process digits from right to left without string conversion
        for (int i = length - 1; i >= 0; i--) {
            int digit = (int)(temp % 10);
            temp /= 10;
            
            if ((length - i) % 2 == 1) {
                intCode[i] = digit;
            } else {
                int doubled = digit * 2;
                intCode[i] = (doubled > 9) ? doubled - 9 : doubled;
            }
        }
        
        System.out.format("%d ", code);
        System.out.println(intCode);
        return intCode;
    }

    public int getCheckSum() {
        // Calculate sum directly without creating array
        long temp = code;
        int length = (temp == 0) ? 1 : 0;
        while (temp > 0) {
            length++;
            temp /= 10;
        }
        
        temp = code;
        int sum = 0;
        
        for (int i = length - 1; i >= 0; i--) {
            int digit = (int)(temp % 10);
            temp /= 10;
            
            if ((length - i) % 2 == 1) {
                sum += digit;
            } else {
                int doubled = digit * 2;
                sum += (doubled > 9) ? doubled - 9 : doubled;
            }
        }
        
        return sum;
    }

    public boolean isValid() {
        return getCheckSum() % 10 == 0;
    }

    public static long create(long code) {
        int checkSum = new Luhn(code * 10).getCheckSum() % 10;
        return (10L * code) + (checkSum == 0 ? 0L : (10L - checkSum));
    }
}