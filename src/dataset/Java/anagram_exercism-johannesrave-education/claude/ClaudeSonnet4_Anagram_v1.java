import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram{
    private final String base;
    private final String baseLower;
    private final char[] baseSorted;
    
    public Anagram(String in){
        this.base = in;
        this.baseLower = in.toLowerCase();
        this.baseSorted = baseLower.toCharArray();
        Arrays.sort(this.baseSorted);
    }
    
    public List match(List<String> candidates) {
        List result = new ArrayList(candidates.size());
        
        for (String candidate : candidates){
            if (candidate.length() != base.length()) continue;
            
            String candidateLower = candidate.toLowerCase();
            if (!baseLower.equals(candidateLower)){
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