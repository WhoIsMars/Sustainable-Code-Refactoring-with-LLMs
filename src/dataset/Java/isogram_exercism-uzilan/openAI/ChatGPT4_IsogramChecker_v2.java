class IsogramChecker {

    boolean isIsogram(String phrase) {
        boolean[] seen = new boolean[26];
        for (char c : phrase.toLowerCase().toCharArray()) {
            if (Character.isLetter(c)) {
                int index = c - 'a';
                if (seen[index]) {
                    return false;
                }
                seen[index] = true;
            }
        }
        return true;
    }
}