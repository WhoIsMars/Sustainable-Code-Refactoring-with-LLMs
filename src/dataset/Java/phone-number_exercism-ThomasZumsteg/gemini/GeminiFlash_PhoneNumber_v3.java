public class PhoneNumber {
    private final String strPhoneNumber;
    private String cachedNumber;

    public PhoneNumber(String strPhoneNumber) {
        this.strPhoneNumber = strPhoneNumber;
        this.cachedNumber = null;
    }

    public String getNumber() {
        if (cachedNumber != null) {
            return cachedNumber;
        }

        String digits = strPhoneNumber.replaceAll("\\D+", "");
        if (digits.length() == 11 && digits.startsWith("1")) {
            digits = digits.substring(1);
        }
        if (digits.length() != 10) {
            cachedNumber = "0000000000";
            return cachedNumber;
        }
        cachedNumber = digits;
        return cachedNumber;
    }

    public String getAreaCode() {
        String number = getNumber();
        return number.substring(0, 3);
    }

    public String pretty() {
        String number = getNumber();
        return "(" + number.substring(0, 3) + ") " +
               number.substring(3, 6) + "-" +
               number.substring(6, 10);
    }
}