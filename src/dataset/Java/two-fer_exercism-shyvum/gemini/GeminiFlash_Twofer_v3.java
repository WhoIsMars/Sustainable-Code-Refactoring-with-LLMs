public class Twofer {
    private static final String DEFAULT_NAME = "you";
    private static final String ONE_FOR = "One for ";
    private static final String COMMA_ONE_FOR_ME = ", one for me.";

    public String twofer(String name) {
        String actualName = (name == null || name.isEmpty()) ? DEFAULT_NAME : name;
        StringBuilder sb = new StringBuilder(ONE_FOR.length() + actualName.length() + COMMA_ONE_FOR_ME.length());
        sb.append(ONE_FOR).append(actualName).append(COMMA_ONE_FOR_ME);
        return sb.toString();
    }
}