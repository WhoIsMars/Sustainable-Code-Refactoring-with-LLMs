import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram{
    private final String baseLower;
    private final char[] baseSorted;
    
    public Anagram(String in){
        this.baseLower = in.toLowerCase();
        this.baseSorted = baseLower.toCharArray();
        Arrays.sort(this.baseSorted);
    }
    
    public List<String> match(List<String> candidates) {
        List<String> result = new ArrayList<>();
        
        for (String candidate : candidates){
            String candidateLower = candidate.toLowerCase();
            if (!baseLower.equals(candidateLower) && candidateLower.length() == baseLower.length()){
                char[] charsToMatch = candidateLower.toCharArray();
                Arrays.sort(charsToMatch);
                if (Arrays.equals(baseSorted, charsToMatch)) {
                    result.add(candidate);
                }
            }
        }
        return result;
    }
}