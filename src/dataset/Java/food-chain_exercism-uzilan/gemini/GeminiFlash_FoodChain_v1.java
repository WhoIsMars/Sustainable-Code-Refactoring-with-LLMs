public class FoodChain {

    private static final String[] ANIMALS = {"fly", "spider", "bird", "cat", "dog", "goat", "cow", "horse"};
    private static final String[] DESCRIPTIONS = {
            "I don't know why she swallowed the fly. Perhaps she'll die.",
            "It wriggled and jiggled and tickled inside her.",
            "How absurd to swallow a bird!",
            "Imagine that, to swallow a cat!",
            "What a hog, to swallow a dog!",
            "Just opened her throat and swallowed a goat!",
            "I don't know how she swallowed a cow!",
            "She's dead, of course!"
    };

    public String verse(int verse) {
        int index = verse - 1;
        StringBuilder sb = new StringBuilder();
        sb.append("I know an old lady who swallowed a ").append(ANIMALS[index]).append(".\n");
        sb.append(DESCRIPTIONS[index]).append("\n");

        if (verse < ANIMALS.length) {
            for (int i = verse - 1; i > 0; i--) {
                sb.append("She swallowed the ").append(ANIMALS[i]).append(" to catch the ").append(ANIMALS[i - 1]);
                if (i == 1) {
                    sb.append(" that wriggled and jiggled and tickled inside her.\n");
                } else {
                    sb.append(".\n");
                }
            }
            sb.append("I don't know why she swallowed the fly. Perhaps she'll die.\n");
        }

        return sb.toString().trim();
    }

    public String verses(int startVerse, int endVerse) {
        StringBuilder sb = new StringBuilder();
        for (int i = startVerse; i <= endVerse; i++) {
            sb.append(verse(i));
            if (i < endVerse) {
                sb.append("\n\n");
            }
        }
        return sb.toString();
    }
}