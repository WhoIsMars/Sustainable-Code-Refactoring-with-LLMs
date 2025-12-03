class ReverseString {

    String reverse(String inputString) {
        if (inputString == null || inputString.length() <= 1) {
            return inputString;
        }
        
        StringBuilder sb = new StringBuilder(inputString.length());
        for (int i = inputString.length() - 1; i >= 0; i--) {
            sb.append(inputString.charAt(i));
        }
        return sb.toString();
    }
  
}