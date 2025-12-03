class Twofer {

    String twofer(String name) {
        String person = (name == null || name.isEmpty()) ? "you" : name;
        return new StringBuilder("One for ").append(person).append(", one for me.").toString();
    }
}