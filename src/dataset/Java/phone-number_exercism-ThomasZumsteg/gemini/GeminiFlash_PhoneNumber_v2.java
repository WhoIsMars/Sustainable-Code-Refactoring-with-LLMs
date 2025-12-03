public class PhoneNumber {
    private final String strPhoneNumber;
    private String cleanedNumber;

    public PhoneNumber(String strPhoneNumber) {
        this.strPhoneNumber = strPhoneNumber;
        this.cleanedNumber = cleanNumber(strPhoneNumber);
    }

    private String cleanNumber(String number) {
        String digits = number.replaceAll("\\D+", "");
        if (digits.length() == 11 && digits.charAt(0) == '1') {
            digits = digits.substring(1);
        }
        if (digits.length() != 10) {
            return "0000000000";
        }
        return digits;
    }

    public String getNumber() {
        return cleanedNumber;
    }

    public String getAreaCode() {
        return cleanedNumber.substring(0, 3);
    }

    public String pretty() {
        return "(" + cleanedNumber.substring(0, 3) + ") " +
               cleanedNumber.substring(3, 6) + "-" +
               cleanedNumber.substring(6, 10);
    }
}