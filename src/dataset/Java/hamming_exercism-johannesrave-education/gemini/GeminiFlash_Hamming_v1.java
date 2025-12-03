public class Hamming {

    private final String leftStrand;
    private final String rightStrand;
    private final int length;

    public Hamming(String leftStrand, String rightStrand) {
        int leftLength = leftStrand.length();
        int rightLength = rightStrand.length();

        if (leftLength != rightLength) {
            if (leftLength == 0) {
                throw new IllegalArgumentException("left strand must not be empty.");
            }
            if (rightLength == 0) {
                throw new IllegalArgumentException("right strand must not be empty.");
            }
            throw new IllegalArgumentException("leftStrand and rightStrand must be of equal length.");
        }

        this.leftStrand = leftStrand;
        this.rightStrand = rightStrand;
        this.length = leftLength;
    }

    public int getHammingDistance() {
        int distance = 0;
        for (int i = 0; i < length; i++) {
            if (leftStrand.charAt(i) != rightStrand.charAt(i)) {
                distance++;
            }
        }
        return distance;
    }
}