class MicroBlog {
    public String truncate(String input) {
        int count = 0;
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < input.length() && count < 5; i++) {
            int codePoint = input.codePointAt(i);
            result.appendCodePoint(codePoint);
            if (Character.isSupplementaryCodePoint(codePoint)) {
                i++;
            }
            count++;
        }
        return result.toString();
    }
}