public class PhoneNumber {
    private final String strPhoneNumber;

    public PhoneNumber(String strPhoneNumber) {
        this.strPhoneNumber = strPhoneNumber;
    }

    public String getNumber() {
        StringBuilder digits = new StringBuilder(10);
        for (int i = 0; i < strPhoneNumber.length(); i++) {
            char c = strPhoneNumber.charAt(i);
            if (Character.isDigit(c)) {
                digits.append(c);
            }
        }
        int length = digits.length();
        if (length == 11 && digits.charAt(0) == '1') {
            digits.deleteCharAt(0);
            length--;
        }
        return length == 10 ? digits.toString() : "0000000000";
    }

    public String getAreaCode() {
        return getNumber().substring(0, 3);
    }

    public String pretty() {
        String digits = getNumber();
        return "(" + digits.substring(0, 3) + ") " +
               digits.substring(3, 6) + "-" +
               digits.substring(6);
    }
}