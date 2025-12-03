class Twofer {

    String twofer(String name) {
        String actualName = (name == null || name.isEmpty()) ? "you" : name;
        return "One for " + actualName + ", one for me.";
    }
}