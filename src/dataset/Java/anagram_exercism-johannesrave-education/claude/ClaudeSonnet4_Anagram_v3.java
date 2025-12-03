import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram{
    private final String base;
    private final char[] sortedBaseChars;
    private final String baseLower;
    
    public Anagram(String in){
        this.base = in;
        this.baseLower = in.toLowerCase();
        this.sortedBaseChars = baseLower.toCharArray();
        Arrays.sort(this.sortedBaseChars);
    }
    
    public List match(List<String> candidates) {
        List result = new ArrayList();
        
        for (String candidate : candidates){
            String candidateLower = candidate.toLowerCase();
            if (!baseLower.equals(candidateLower) && 
                candidateLower.length() == baseLower.length()){
                char[] candidateChars = candidateLower.toCharArray();
                Arrays.sort(candidateChars);
                if (Arrays.equals(sortedBaseChars, candidateChars)) {
                    result.add(candidate);
                }
            }
        }
        return result;
    }
}