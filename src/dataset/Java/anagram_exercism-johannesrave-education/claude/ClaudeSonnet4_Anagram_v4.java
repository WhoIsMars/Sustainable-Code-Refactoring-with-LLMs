import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram{
    private final String base;
    private final char[] baseSorted;
    private final String baseLower;
    
    public Anagram(String in){
        this.base = in;
        this.baseLower = in.toLowerCase();
        this.baseSorted = baseLower.toCharArray();
        Arrays.sort(this.baseSorted);
    }
    
    public List<String> match(List<String> candidates) {
        List<String> result = new ArrayList<>();
        
        for (String candidate : candidates){
            String candidateLower = candidate.toLowerCase();
            if (!baseLower.equals(candidateLower) && 
                candidate.length() == base.length()){
                char[] candidateChars = candidateLower.toCharArray();
                Arrays.sort(candidateChars);
                if (Arrays.equals(baseSorted, candidateChars)) {
                    result.add(candidate);
                }
            }
        }
        return result;
    }
}