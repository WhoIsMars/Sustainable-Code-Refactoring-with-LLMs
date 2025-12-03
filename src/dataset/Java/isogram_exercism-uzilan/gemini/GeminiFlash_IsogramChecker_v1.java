class IsogramChecker {

    boolean isIsogram(String phrase) {
        phrase = phrase.toLowerCase();
        int[] charCounts = new int[26]; // Assuming only ASCII letters

        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            if (Character.isLetter(c)) {
                int index = c - 'a';
                if (charCounts[index] > 0) {
                    return false;
                }
                charCounts[index]++;
            }
        }

        return true;
    }
}