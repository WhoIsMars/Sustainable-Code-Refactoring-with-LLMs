public class PigLatin {

    private static final String VOWELS = "aeiou";

    public static String translate(String input) {
        String[] words = input.split(" ");
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < words.length; i++) {
            result.append(translateWord(words[i]));
            if (i < words.length - 1) {
                result.append(" ");
            }
        }

        return result.toString();
    }

    private static String translateWord(String input) {
        int firstVowelIndex = -1;
        for (int i = 0; i < input.length(); i++) {
            if (VOWELS.indexOf(input.charAt(i)) != -1) {
                firstVowelIndex = i;
                break;
            }
            if (input.charAt(i) == 'y') {
                if (i == 0) continue;
                firstVowelIndex = i;
                break;
            }
        }

        if (firstVowelIndex == -1) {
            return input + "ay";
        }

        if (input.startsWith("qu")) {
            return input.substring(2) + "quay";
        }

        for (int i = 0; i < input.length() - 1; i++) {
            if (input.substring(i, i + 2).equals("qu") && (i < firstVowelIndex)) {
                return input.substring(i + 2) + input.substring(0, i + 2) + "ay";
            }
        }

        if (firstVowelIndex == 0) {
            return input + "ay";
        }

        return input.substring(firstVowelIndex) + input.substring(0, firstVowelIndex) + "ay";
    }
}