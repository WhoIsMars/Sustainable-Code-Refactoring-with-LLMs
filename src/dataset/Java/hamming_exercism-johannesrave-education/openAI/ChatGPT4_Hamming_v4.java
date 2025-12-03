public class Hamming {

    private final String left;
    private final String right;

    public Hamming(String leftStrand, String rightStrand) {
        if (leftStrand == null || rightStrand == null) {
            throw new IllegalArgumentException("Strands must not be null.");
        }
        if (leftStrand.isEmpty()) {
            throw new IllegalArgumentException("left strand must not be empty.");
        }
        if (rightStrand.isEmpty()) {
            throw new IllegalArgumentException("right strand must not be empty.");
        }
        if (leftStrand.length() != rightStrand.length()) {
            throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
        }
        this.left = leftStrand;
        this.right = rightStrand;
    }

    public int getHammingDistance() {
        int distance = 0;
        for (int i = 0, len = left.length(); i < len; i++) {
            if (left.charAt(i) != right.charAt(i)) {
                distance++;
            }
        }
        return distance;
    }
}