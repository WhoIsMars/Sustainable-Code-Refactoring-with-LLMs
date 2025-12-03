public class Twofer {
    private static final String PREFIX = "One for ";
    private static final String SUFFIX = ", one for me.";
    private static final String DEFAULT_NAME = "you";
    
    public String twofer(String name) {
        if (name == null || name.isEmpty()) {
            return PREFIX + DEFAULT_NAME + SUFFIX;
        }
        return PREFIX + name + SUFFIX;
    }
}