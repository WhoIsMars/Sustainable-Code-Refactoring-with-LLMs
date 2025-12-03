public class Twofer {
    public String twofer(String name) {
        return "One for " + (name == null || name.isBlank() ? "you" : name) + ", one for me.";
    }
}