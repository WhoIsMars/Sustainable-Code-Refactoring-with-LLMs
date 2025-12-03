public class Hamming {
    
    private final String left;
    private final String right;
    private final int length;
    
    public Hamming(String leftStrand, String rightStrand) {
        int ll = leftStrand.length();
        int rl = rightStrand.length();
        if (ll != rl) {
            if(ll == 0) throw new IllegalArgumentException("left strand must not be empty.");
            if(rl == 0) throw new IllegalArgumentException("right strand must not be empty.");
            throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
        }
        this.left = leftStrand;
        this.right = rightStrand;
        this.length = ll;
    }       
    
    public int getHammingDistance() {
        int distance = 0;
        for (int i = 0; i < length; i++){
            if (left.charAt(i) != right.charAt(i)) distance++;
        }
        return distance;
    }
}