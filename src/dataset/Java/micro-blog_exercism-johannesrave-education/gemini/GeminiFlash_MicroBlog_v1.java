class MicroBlog {
    public String truncate(String input) {
        int count = 0;
        int index = 0;
        for (int i = 0; i < input.length(); ) {
            int codepoint = input.codePointAt(i);
            if (count >= 5) {
                break;
            }
            count++;
            index += Character.charCount(codepoint);
            i += Character.charCount(codepoint);
        }
        return input.substring(0, index);
    }
}