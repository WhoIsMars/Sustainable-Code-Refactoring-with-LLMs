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
        this.baseSorted = this.baseLower.toCharArray();
        Arrays.sort(this.baseSorted);
    }
    
    public List<String> match(List<String> candidates) {
        List<String> result = new ArrayList<>();
        
        for (String candidate : candidates){
            String candidateLower = candidate.toLowerCase();
            if (!baseLower.equals(candidateLower) && base.length() == candidate.length()){
                char[] candidateSorted = candidateLower.toCharArray();
                Arrays.sort(candidateSorted);
                if (Arrays.equals(baseSorted, candidateSorted)) {
                    result.add(candidate);
                }
            }
        }
        return result;
    }
}