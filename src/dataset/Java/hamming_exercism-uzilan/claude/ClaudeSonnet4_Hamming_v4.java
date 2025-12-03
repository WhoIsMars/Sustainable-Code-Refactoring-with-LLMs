import java.util.Objects;

class Hamming {

    private final String leftStrand;
    private final String rightStrand;

    Hamming(String leftStrand, String rightStrand) {
        Objects.requireNonNull(leftStrand, "leftStrand cannot be null");
        Objects.requireNonNull(rightStrand, "rightStrand cannot be null");
        
        if (leftStrand.length() != rightStrand.length()) {
            throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
        }

        this.leftStrand = leftStrand;
        this.rightStrand = rightStrand;
    }

    long getHammingDistance() {
        final int length = leftStrand.length();
        long distance = 0;
        
        for (int i = 0; i < length; i++) {
            if (leftStrand.charAt(i) != rightStrand.charAt(i)) {
                distance++;
            }
        }
        
        return distance;
    }
}