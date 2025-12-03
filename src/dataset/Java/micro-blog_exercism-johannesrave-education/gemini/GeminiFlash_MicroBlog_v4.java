class MicroBlog {
    public String truncate(String input) {
        int count = 0;
        int index = 0;
        for (int i = 0; i < input.length(); i++) {
            if (Character.isHighSurrogate(input.charAt(i))) {
                if (i + 1 < input.length() && Character.isLowSurrogate(input.charAt(i + 1))) {
                    i++;
                }
            }
            if (count < 5) {
                count++;
                index = i + 1;
            } else {
                break;
            }
        }
        return input.substring(0, index);
    }
}