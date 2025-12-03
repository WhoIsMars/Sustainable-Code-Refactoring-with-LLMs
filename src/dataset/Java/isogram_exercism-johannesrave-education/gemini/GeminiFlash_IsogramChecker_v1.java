class IsogramChecker {

    boolean isIsogram(String phrase) {
        String cleanPhrase = phrase.replaceAll("\\W", "").toLowerCase();
        int length = cleanPhrase.length();

        if (length > 26) {
            return false; // Optimization: More than 26 unique chars is impossible
        }

        HashSet<Character> seenChars = new HashSet<>(length); // Initialize with expected size

        for (int i = 0; i < length; i++) {
            char c = cleanPhrase.charAt(i);
            if (!seenChars.add(c)) {
                return false; // Early exit if duplicate found
            }
        }

        return true;
    }
}