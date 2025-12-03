class MicroBlog {
    public String truncate(String input) {
        int count = 0;
        int[] codePoints = input.codePoints().toArray();
        int length = codePoints.length;
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < length; i++) {
            if (count < 5) {
                sb.appendCodePoint(codePoints[i]);
                count++;
            } else {
                break;
            }
        }
        return sb.toString();
    }
}