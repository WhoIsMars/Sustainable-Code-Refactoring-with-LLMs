public class Binary {
    private final String binary;
    private int cachedDecimal = -1;
    private boolean isValidated = false;

    public Binary(String binary) {
        this.binary = binary;
    }

    public int getDecimal() {
        if (cachedDecimal != -1) {
            return cachedDecimal;
        }

        if (binary == null || binary.isEmpty()) {
            return cachedDecimal = 0;
        }

        int result = 0;
        int length = binary.length();
        
        for (int i = 0; i < length; i++) {
            char c = binary.charAt(i);
            if (c != '0' && c != '1') {
                return cachedDecimal = 0;
            }
            if (c == '1') {
                result = (result << 1) | 1;
            } else {
                result = result << 1;
            }
        }
        
        return cachedDecimal = result;
    }
}