class MicroBlog {
    public String truncate(String input) {
        if (input == null || input.length() <= 5) {
            return input;
        }
        
        int count = 0;
        int index = 0;
        
        while (index < input.length() && count < 5) {
            int codePoint = input.codePointAt(index);
            index += Character.charCount(codePoint);
            count++;
        }
        
        return input.substring(0, index);
    }
}