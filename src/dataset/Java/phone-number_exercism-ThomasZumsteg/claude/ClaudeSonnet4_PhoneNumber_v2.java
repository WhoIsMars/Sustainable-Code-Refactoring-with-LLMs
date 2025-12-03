public class PhoneNumber {
    private String normalizedNumber;

    public PhoneNumber(String strPhoneNumber) {
        this.normalizedNumber = normalizeNumber(strPhoneNumber);
    }

    private String normalizeNumber(String phoneNumber) {
        StringBuilder digits = new StringBuilder(11);
        for (int i = 0; i < phoneNumber.length(); i++) {
            char c = phoneNumber.charAt(i);
            if (c >= '0' && c <= '9') {
                digits.append(c);
            }
        }
        
        int length = digits.length();
        if (length == 11 && digits.charAt(0) == '1') {
            return digits.substring(1);
        }
        if (length != 10) {
            return "0000000000";
        }
        return digits.toString();
    }

    public String getNumber() {
        return normalizedNumber;
    }

    public String getAreaCode() {
        return normalizedNumber.substring(0, 3);
    }

    public String pretty() {
        return "(" + normalizedNumber.substring(0, 3) + ") " +
               normalizedNumber.substring(3, 6) + "-" +
               normalizedNumber.substring(6, 10);
    }
}